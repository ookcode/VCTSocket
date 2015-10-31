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
            virtual void recvPackage(Package *package) = 0;
        };
        
        //创建一个socket的工厂方法
        static SocketThread* create(Delegate *delegate);
        
        //析构
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
        //构造
        SocketThread(Delegate *delegate);
        
        //收到数据
        void onRead(char* buffer,int size);
        
        //监听线程
        void onRecvThread();
        
        //分发包线程
        void onDispatchThread(float dt);
        
        //发送心跳包线程
        void onHeartBeatThread(float dt);
        
        //添加到发送队列
        void addToDispatchThread(Package *pack);
        
        Socket *_socket = nullptr;
        std::thread *_recvThread = nullptr;
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
