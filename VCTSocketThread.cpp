//
//  VCTSocketThread.cpp
//  VCTSocketClient
//
//  Created by Vincent on 15/9/1.
//  Copyright (c) 2015年 Vincent. All rights reserved.
//

#include "VCTSocketThread.h"
#include "VCTSocket.h"
#include <unistd.h>
#include "cocos2d.h"

namespace VCT {
    
#define SCHEDULE() cocos2d::Director::getInstance()->getScheduler()
#define DispatchThreadKey "SocketThread::onDispatchThread"
#define HeartBeatThreadKey "SocketThread::onHeartBeatThread"
    SocketThread* SocketThread::create(Delegate *delegate) {
        SocketThread *thread = new SocketThread(delegate);
        if (thread) {
            return thread;
        }
        DELETE(thread);
        return nullptr;
    }
    
    SocketThread::SocketThread(Delegate *delegate) {
        _delegate = delegate;
    }
    
    SocketThread::~SocketThread() {
        close();
        //清空消息队列
        auto iter = _packageDeque.begin();
        while (iter != _packageDeque.end()) {
            Package *pack = *iter;
            DELETE(pack);
            _packageDeque.erase(iter);
        }
    }
    
    void SocketThread::openWithIp(const char* ip, int port) {
        if (!_connected) {
            _socket = new Socket(ip,port);
            //启动socket接收线程
            _recvThread = new std::thread(std::bind(&SocketThread::onRecvThread, this));
            //启动包的分发线程
            SCHEDULE()->schedule(CC_CALLBACK_1(SocketThread::onDispatchThread, this), this, 0.1f, false, DispatchThreadKey);
            //启动心跳包线程
            SCHEDULE()->schedule(CC_CALLBACK_1(SocketThread::onHeartBeatThread, this), this, 1.0f, false, HeartBeatThreadKey);
        }else {
            printf("error exec openWithIp, already connected\n");
        }
    }
    
    void SocketThread::onRecvThread() {
        //连接socket
        int n = _socket->connect();
        if (n != Socket::CONNECT_SUCCESS) {
            //连接失败
            Package* pack = new NET_ERROR_PACKAGE;
            addToDispatchThread(pack);
            return;
        }
        Package *connected = new CONNECT_SUCCESS_PACKAGE;
        addToDispatchThread(connected);
        _connected = true;
        
        char buffer[RECV_SIZE];
        
        timeval timeOut;
        timeOut.tv_sec = 0;
        timeOut.tv_usec = 16000;
        
        while (_connected) {//断开连接后退出线程
            //监听消息
            int nready = _socket->select(&timeOut);
            
            if (0 == nready) {
                //select = 0：等待超时，没有可读写或错误的文件
                continue;
            }
            
            if (nready < 0) {
                //select = 负值：select错误
                Package* pack = new NET_ERROR_PACKAGE;
                addToDispatchThread(pack);
                break;
            }
            //slect = 正值：某些文件可读写
            int recvSize = _socket->recv(buffer, RECV_SIZE);
            if (recvSize == -1) {
                //网络错误
                Package* pack = new NET_ERROR_PACKAGE;
                addToDispatchThread(pack);
                break;
            }
            if (recvSize == 0) {
                //服务端关闭socket连接
                Package* pack = new SERVER_CLOSE_PACKAGE;
                addToDispatchThread(pack);
                break;
            }
            onRead(buffer, recvSize);
        };
        return;
    }
    
    void SocketThread::onDispatchThread(float dt) {
        Package *pack = nullptr;
        std::lock_guard < std::mutex > autoLock(_packageDequeLock);
        if (!_packageDeque.empty()) {
            pack = _packageDeque.front();
            if(_delegate) _delegate->recvPackage(pack);
            _packageDeque.pop_front();
            DELETE(pack);
        }
    }
    
    void SocketThread::onHeartBeatThread(float dt) {
        if (_connected) {
            Package *heartbeat = new HEART_BEAT_PACKAGE;
            sendPackage(heartbeat);//发送心跳包
            std::lock_guard <std::mutex> lock(_heartBeatLock);
            _heartBeatDiff++;
            if (_heartBeatDiff >= 3) {
                //如果心跳包差值超过一定值，发送断线消息
                Package* pack = new NET_TIMEOUT_PACKAGE;
                addToDispatchThread(pack);
            }
            DELETE(heartbeat);
        }
    }
    
    void SocketThread::onRead(char *buffer, int size) {
        //分包与合包
        _cache.insert(_cache.end(), buffer,buffer + size);
        
        //凑齐至少一个包头再处理
        while (_cache.size() >= PACKAGE_HEAD_SIZE) {
            
            //取出包头
            PACKAGE_HEAD *head = (PACKAGE_HEAD *)_cache.data();

            if (_cache.size() >= head->size) {
                if (head->mainID == MAIN_NET_BASE && head->assID == ass_heart_beat) {
                    //收到一个心跳包
                    std::lock_guard <std::mutex> lock(_heartBeatLock);
                    _heartBeatDiff--;
                }else{
                    //取出一个包
                    Package *pack = new Package(_cache.data(), head->size);
                    //添加到分发队列
                    addToDispatchThread(pack);
                    
                }
                _cache.erase(_cache.begin(),_cache.begin() + head->size);
            }
        }
    }
    
    void SocketThread::sendPackage(Package *package) {
        int ret = _socket->send(package->getPackage(), package->getSize());
        if (ret == -1) {
            Package *pack = new NET_ERROR_PACKAGE;
            addToDispatchThread(pack);
        }
    }
    
    void SocketThread::addToDispatchThread(Package *pack) {
        std::lock_guard <std::mutex> lock(_packageDequeLock);
        _packageDeque.push_back(pack);
    }
    
    void SocketThread::close() {
        _connected = false;
        
        //停止recv线程
        if (_recvThread && _recvThread->joinable()) {
            _recvThread->join();
        }
        DELETE(_recvThread);
        
        //关闭socket连接
        if(_socket) _socket->close();
        DELETE(_socket);
        
        SCHEDULE()->unschedule(DispatchThreadKey, this);
        SCHEDULE()->unschedule(HeartBeatThreadKey, this);
    }
    
}