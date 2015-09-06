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
        
        
        static SocketThread* create(Delegate *delegate);
        void destory();
        ~SocketThread();
        void openWithIp(const char* ip,int port);
        void sendPackage(Package *package);
        void close();
        inline bool isConnected() {
            return _connected;
        }
        
    private:
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
