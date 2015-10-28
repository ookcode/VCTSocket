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
    
    SocketLogic::SocketLogic() {
        addListener(MAIN_NET_BASE, ass_server_close, SEL_LISTENER(SocketLogic::onDisConnected,this));
        addListener(MAIN_NET_BASE, ass_net_error, SEL_LISTENER(SocketLogic::onDisConnected,this));
        addListener(MAIN_NET_BASE, ass_net_timeout, SEL_LISTENER(SocketLogic::onDisConnected,this));
        addListener(MAIN_NET_BASE, ass_connect_success, SEL_LISTENER(SocketLogic::onConnected,this));
    }
    
    SocketLogic::~SocketLogic() {
        removeListener(MAIN_NET_BASE, ass_server_close);
        removeListener(MAIN_NET_BASE, ass_net_error);
        removeListener(MAIN_NET_BASE, ass_net_timeout);
        removeListener(MAIN_NET_BASE, ass_connect_success);
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
    
    void SocketLogic::sendPackage(UINT mainID,UINT assID,UINT handleID,void* body,int bodySize,PackageListener listener) {
        
        addListener(mainID, assID, listener);
        
        Package* package = new Package(mainID,assID,handleID,body,bodySize);
        _thread->sendPackage(package);
        DELETE(package);
    }
    
    void SocketLogic::addListener(UINT mainID,UINT assID,PackageListener listener) {
        if (listener) {
            char ckey[16] = {0};
            sprintf(ckey, "%d_%d",mainID,assID);
            _listeners[std::string(ckey)].push_back(listener);
        }
    }
    
    void SocketLogic::removeListener(UINT mainID, UINT assID) {
        char ckey[16] = {0};
        sprintf(ckey, "%d_%d",mainID,assID);
        auto iter = _listeners.find(std::string(ckey));
        if (iter != _listeners.end()) {
            iter->second.pop_back();
            if (iter->second.empty()) {
                _listeners.erase(iter);
            }
        }
    }
/**************************************************
*  listener
***************************************************/
    bool SocketLogic::onConnected(Package *package) {
        printf("onConnected\n");
        return true;
    }
    
    bool SocketLogic::onDisConnected(Package *package) {
        int assID = package->getAssID();
        printf("onDisConnected errorCode = %d\n",assID);
        return true;
    }
    
/**************************************************
 *  delegate
 ***************************************************/
    
    void SocketLogic::recvPackage(Package *package) {
        UINT mainID = package->getMainID();
        UINT assID = package->getAssID();
        char ckey[16] = {0};
        sprintf(ckey, "%d_%d",mainID,assID);
        //遍历观察者，执行回调，若回调返回true，停止继续下发
        auto iter = _listeners.find(std::string(ckey));
        if (iter != _listeners.end()) {
            for (auto riter = iter->second.rbegin(); riter != iter->second.rend(); ++riter) {
                if ((*riter)(package)) {
                    break;
                }
            }
        }
    };
}