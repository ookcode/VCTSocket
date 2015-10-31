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
        DELETE(_thread);
        _thread = SocketThread::create(this);
        _thread->openWithIp(ip, port);
    }
    
    void SocketLogic::close() {
        DELETE(_thread);
    }
    
    void SocketLogic::sendPackage(Package *package) {
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
 *  delegate,夹上宏不进行jsbinding
 ***************************************************/
#ifdef COCOS2D_JAVASCRIPT
    void SocketLogic::recvPackage(Package *package) {
        UINT mainID = package->getMainID();
        UINT assID = package->getAssID();
        char ckey[16] = {0};
        sprintf(ckey, "%d_%d",mainID,assID);
        //遍历观察者，执行回调，若回调返回true，停止继续下发
        auto iter = _listeners.find(std::string(ckey));
        if (iter != _listeners.end()) {
            for (auto riter = iter->second.rbegin(); riter != iter->second.rend(); ++riter) {
                PackageListener listener = *riter;
                if (listener(package)) {
                    break;
                }
            }
        }
    };
#endif
}