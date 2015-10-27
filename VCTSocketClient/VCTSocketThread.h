//
//  VCTSocketThread.h
//  VCTSocketClient
//
//  Created by Vincent on 15/9/1.
//  Copyright (c) 2015年 Vincent. All rights reserved.
//

#ifndef __VCTSocketClient__VCTSocketThread__
#define __VCTSocketClient__VCTSocketThread__

#include <thread>
#include <vector>
#include <deque>
#include <functional>
#include <mutex>
#include <stdlib.h>
#include "VCTPackage.h"

namespace VCT {
    class Socket;
    class Package;
    class SocketThread {
    public:
        class Delegate {
        public:
            virtual void onConnected() = 0;
            virtual void onDisConnected() = 0;
            virtual void recvPackage(Package *package) = 0;
        };
        
        //创建一个socket的工厂方法
        static SocketThread* create(Delegate *delegate);
        
        //销毁工厂
        void destory();
        
        ~SocketThread();
        
        //连接指定IP
        void openWithIp(const char* ip,int port);
        
        //发包
        void sendPackage(Package *package);
        
        //关闭socket连接
        void close();
        
        //判断是否已连接
        inline bool isConnected() {
            return _connected;
        }
        
    private:
        
        //屏蔽delete重载，请使用destory()销毁
        inline void operator delete(void *p)
        {
            free(p);
        }
        
        SocketThread(Delegate *delegate);
        
        void onRead(char* buffer,int size);
        
        void onRecvThread();
        void onDispatchThread();
        void onHeartBeatThread();
        
        void addToDispatchThread(Package *pack);
        
        Socket *_socket = nullptr;
        std::thread *_recvThread = nullptr;
        std::thread *_dispatchThread = nullptr;
        std::thread *_heartbeatThread = nullptr;
        Delegate *_delegate = nullptr;
        
        std::vector<char> _cache;
        std::deque<Package *> _packageDeque;
        std::mutex _packageDequeLock;
        std::mutex _heartBeatLock;
        
        bool _connected = false;
        int _heartBeatDiff = 0;
    };
}
#endif /* defined(__VCTSocketClient__VCTSocketThread__) */
