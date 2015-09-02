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
        SocketThread(Delegate *delegate);
        ~SocketThread();
        void openWithIp(const char* ip,int port);
        void sendPackage(Package *package);
        
        inline bool isConnected() {
            return _connected;
        }
        
    private:
        void onRecvThread();
        void onRead(char* buffer,int size);
        void onDispatchThread();
        
        Socket *_socket = nullptr;
        std::thread *_recvThread = nullptr;
        std::thread *_dispatchThread = nullptr;
        Delegate *_delegate = nullptr;
        
        std::vector<char> _cache;
        std::deque<Package *> _packageDeque;
        std::mutex _packageDequeLock;
        
        bool _connected = false;
    };
}
#endif /* defined(__VCTSocketClient__VCTSocketThread__) */
