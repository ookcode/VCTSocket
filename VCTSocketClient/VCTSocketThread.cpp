//
//  VCTSocketThread.cpp
//  VCTSocketClient
//
//  Created by Vincent on 15/9/1.
//  Copyright (c) 2015年 Vincent. All rights reserved.
//

#include "VCTSocketThread.h"
#include "VCTSocket.h"
#include "VCTPackage.h"
#include <unistd.h>

namespace VCT {
    SocketThread* SocketThread::create(Delegate *delegate) {
        SocketThread *thread = new SocketThread(delegate);
        if (thread) {
            return thread;
        }
        DELETE(thread);
        return nullptr;
    }
    
    void SocketThread::destory() {
        delete this;
    }
    
    SocketThread::SocketThread(Delegate *delegate) {
        _delegate = delegate;
    }
    
    SocketThread::~SocketThread() {
        close();
        if (_dispatchThread->joinable()) {
            _dispatchThread->join();
        }
        DELETE(_dispatchThread);
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
            _recvThread = new std::thread(std::bind(&SocketThread::onRecvThread, this));
            _dispatchThread = new std::thread(std::bind(&SocketThread::onDispatchThread,this));
        }else {
            printf("error exec openWithIp, already connected\n");
        }
    }
    
    void SocketThread::onRecvThread() {
        int n = _socket->connect();
        if (n != Socket::CONNECT_SUCCESS) {
            //connect fail
            _delegate->onDisConnected();//memory leak
            return;
        }
        //connect successfully
        _delegate->onConnected();
        _connected = true;
        
        //send heartbeat package
        _heartbeatThread = new std::thread(std::bind(&SocketThread::onHeartBeatThread, this));
        
        char buffer[RECV_SIZE];
        
        timeval timeOut;
        timeOut.tv_sec = 0;
        timeOut.tv_usec = 16000;
        
        while (_connected) {

            int nready = _socket->select(&timeOut);
            
            if (0 == nready) {
                // time out
                continue;
            }
            
            if (nready < 0) {
                // network error
                printf("select error\n");
                break;
            }
            int recvSize = _socket->recv(buffer, RECV_SIZE);
            if (recvSize == -1) {
                //network error
                Package* pack = new Package(Package::ERROR, 0, 0, 0, nullptr, 0);
                addToDispatchThread(pack);
                break;
            }
            if (recvSize == 0) {
                //server close
                Package* pack = new Package(Package::ERROR, 0, 0, 0, nullptr, 0);
                addToDispatchThread(pack);
                break;
            }
            onRead(buffer, recvSize);
        };
        return;
    }
    
    void SocketThread::onDispatchThread() {
        
        Package *package = nullptr;
        while (true) {
            std::lock_guard < std::mutex > autoLock(_packageDequeLock);
            if (!_packageDeque.empty()) {
                package = _packageDeque.front();
                if (package->getType() == Package::ERROR) {
                    //close thread
                    close();
                }else {
                    //dispatch to main thread
                    _delegate->recvPackage(package);
                }
                _packageDeque.pop_front();
                DELETE(package);
            }
            usleep(10e+5);//equals 0.1 second
        }
    }
    
    void SocketThread::onHeartBeatThread() {
        Package *heartbeat = new Package(Package::SEND,0, 0, 0, nullptr, 0);
        while (true) {
            sleep(1);
            if (!_connected) break;
            sendPackage(heartbeat);
            std::lock_guard <std::mutex> lock(_heartBeatLock);
            _heartBeatDiff++;
            //printf("heartBeatDiff %d\n",_heartBeatDiff);
            if (_heartBeatDiff >= 3) {
                //add to dispatch deque
                Package* pack = new Package(Package::ERROR, 0, 0, 0, nullptr, 0);
                addToDispatchThread(pack);
                break;
            }
        }
        DELETE(heartbeat);
    }
    
    void SocketThread::onRead(char *buffer, int size) {
        //package split and combine
        _cache.insert(_cache.end(), buffer,buffer + size);
        
        //at least contain one package
        while (_cache.size() >= PACKAGE_HEAD_SIZE) {
            
            //get package head
            PACKAGE_HEAD *head = (PACKAGE_HEAD *)_cache.data();

            //check package
            if (_cache.size() >= head->size) {
                if (head->size == PACKAGE_HEAD_SIZE) {
                    //heartbeat package
                    std::lock_guard <std::mutex> lock(_heartBeatLock);
                    _heartBeatDiff--;
                }else{
                    //get one package
                    Package *pack = new Package(Package::RECV, _cache.data(), head->size);
                    //add to dispatch deque
                    addToDispatchThread(pack);
                    
                }
                _cache.erase(_cache.begin(),_cache.begin() + head->size);
            }
        }
    }
    
    void SocketThread::sendPackage(Package *package) {
        int ret = _socket->send(package->getPackage(), package->getSize());
        if (ret == -1) {
            Package *pack = new Package(Package::ERROR,0,0,0,nullptr,0);
            addToDispatchThread(pack);
        }
    }
    
    void SocketThread::addToDispatchThread(Package *pack) {
        std::lock_guard <std::mutex> lock(_packageDequeLock);
        _packageDeque.push_back(pack);
    }
    
    void SocketThread::close() {
        
        if (!_connected) {
            printf("error exec close, already closed\n");
            return;
        }
        _connected = false;
        if (_heartbeatThread->joinable()) {
            _heartbeatThread->join();
        }
        
        if (_recvThread->joinable()) {
            _recvThread->join();
        }
        printf("delete\n");
        _socket->close();
        DELETE(_heartbeatThread);
        DELETE(_recvThread);
        DELETE(_socket);
        _delegate->onDisConnected();
        
    }
    
}