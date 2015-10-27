//
//  VCTSocketLogic.cpp
//  VCTSocketClient
//
//  Created by Vincent on 15/10/27.
//  Copyright © 2015年 Vincent. All rights reserved.
//

#include "VCTSocketLogic.h"
namespace VCT {
    SocketLogic* SocketLogic::getInstance() {
        static SocketLogic* instance = nullptr;
        if (!instance) {
            instance = new SocketLogic();
        }
        return instance;
    }
    
    void SocketLogic::openWithIp(const char* ip,int port) {
        if (_thread) {
            _thread->destory();
            _thread = nullptr;
        }
        _thread = SocketThread::create(this);
        _thread->openWithIp(ip, port);
    }
    
    void SocketLogic::close() {
        _thread->destory();
        _thread = nullptr;
    }
    
    void SocketLogic::onConnected() {
        printf("onConnected\n");
    };
    
    void SocketLogic::onDisConnected() {
        printf("onDisConnected\n");
    };
    
    void SocketLogic::recvPackage(Package *package) {
        printf("recvPackage\n");
    };
}