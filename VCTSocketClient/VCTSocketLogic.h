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
    class SocketLogic : public SocketThread::Delegate {
    public:
        #define SEL_LISTENER(__selector__,__target__, ...) std::bind(&__selector__,__target__, std::placeholders::_1, ##__VA_ARGS__)
        
        typedef std::function<bool(Package *package)> PackageListener;
        
        static SocketLogic* getInstance();
        
        ~SocketLogic();
        
        //连接指定IP
        void openWithIp(const char* ip,int port);
        
        //关闭socket
        void close();
        
        //发送包
        void sendPackage(UINT mainID,UINT assID,UINT handleID,void* body,int bodySize,PackageListener listener);
        
        //添加观察者
        void addListener(UINT mainID,UINT assID,PackageListener listener);
        
        //移除观察者
        void removeListener(UINT mainID,UINT assID);
        
    private:
        SocketLogic();
        
        //delegate
    public:
        virtual void recvPackage(Package *package) override;
        
        //listener
    private:
        bool onConnected(Package *package);
        bool onDisConnected(Package *package);
        
    private:
        SocketThread *_thread = nullptr;
        std::unordered_map<std::string,std::vector<PackageListener>> _listeners;
    };
}

#endif /* VCTSocketLogic_h */
