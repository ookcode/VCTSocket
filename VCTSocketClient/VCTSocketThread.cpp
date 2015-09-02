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
    SocketThread::SocketThread(Delegate *delegate) {
        _delegate = delegate;
    }
    
    SocketThread::~SocketThread() {
        _connected = false;
        if (_recvThread->joinable()) {
            _recvThread->join();
        }
        if (_dispatchThread->joinable()) {
            _dispatchThread->join();
        }
        DELETE(_socket);
        DELETE(_recvThread);
        DELETE(_dispatchThread);
    }
    
    void SocketThread::openWithIp(const char* ip, int port) {
        if (!_connected) {
            _socket = new Socket(ip,port);
            _recvThread = new std::thread(std::bind(&SocketThread::onRecvThread, this));
            _dispatchThread = new std::thread(std::bind(&SocketThread::onDispatchThread,this));
        }
    }
    
    void SocketThread::onRecvThread() {
        int n = _socket->connect();
        if (n != Socket::CONNECT_SUCCESS) {
            _delegate->onDisConnected();
            return;
        }
        //connect successfully
        _delegate->onConnected();
        _connected = true;
        
        while (true) {
            char buffer[RECV_SIZE];
            int recvSize = _socket->recv(buffer, RECV_SIZE);
            if (recvSize == -1) {
                //network error
                break;
            }
            if (recvSize == 0) {
                //server close
                break;
            }
            onRead(buffer, recvSize);
        };
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
                //get one package
                Package *package = new Package(head, _cache.data() + PACKAGE_HEAD_SIZE, head->size - PACKAGE_HEAD_SIZE);
                
                //add to dispatch deque
                std::lock_guard <std::mutex> lock(_packageDequeLock);
                _packageDeque.push_back(package);
                
                _cache.erase(_cache.begin(),_cache.begin() + head->size);
            }
        }
    }
    
    void SocketThread::onDispatchThread() {
        Package *package = nullptr;
        while (true) {
            std::lock_guard < std::mutex > autoLock(_packageDequeLock);
            if (!_packageDeque.empty()) {
                package = _packageDeque.front();
                
                //dispatch to main thread
                _delegate->recvPackage(package);
                
                _packageDeque.pop_front();
                DELETE(package);
            }
            usleep(10e+5);//equals 0.1 second
        }
    }
    
    void SocketThread::sendPackage(Package *package) {
        int ret = _socket->send(package->getPackage(), package->getSize());
        if (ret == -1) {
            //error
        }
    }
    
}