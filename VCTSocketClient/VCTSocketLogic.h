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

namespace VCT {
    class SocketLogic : public SocketThread::Delegate {
    public:
        static SocketLogic* getInstance();
        
        //连接指定IP
        void openWithIp(const char* ip,int port);
        
        //关闭socket
        void close();
        
    public:
        virtual void onConnected() override;
        virtual void onDisConnected() override;
        virtual void recvPackage(Package *package) override;
        
    private:
        SocketThread *_thread = nullptr;
    };
}

#endif /* VCTSocketLogic_h */
