//
//  VCTSocketLogic.h
//  VCTSocketClient
//
//  Created by Vincent on 15/10/27.
//  Copyright © 2015年 Vincent. All rights reserved.
//

#ifndef VCTSocketLogic_h
#define VCTSocketLogic_h

#include "VCTSocketThread.h"
#include <unordered_map>
#include <string>
#include <vector>

namespace VCT {
    //夹上宏不进行jsbinding
#ifdef COCOS2D_JAVASCRIPT
    class SocketLogic : public SocketThread::Delegate {
#else
    class SocketLogic {
#endif
    public:
        typedef std::function<bool(Package *package)> PackageListener;
        
        static SocketLogic* getInstance();
        
        //连接指定IP
        void openWithIp(const char* ip,int port);
        
        //关闭socket
        void close();
        
        //发送包
        void sendPackage(Package *package);
        
        //添加观察者
        void addListener(UINT mainID,UINT assID,PackageListener listener);
        
        //移除观察者
        void removeListener(UINT mainID,UINT assID);
        
        //delegate,夹上宏不进行jsbinding
#ifdef COCOS2D_JAVASCRIPT
    public:
        virtual void recvPackage(Package *package) override;
#endif
        
    private:
        SocketThread *_thread = nullptr;
        std::unordered_map<std::string,std::vector<PackageListener>> _listeners;
    };
}

#endif /* VCTSocketLogic_h */
