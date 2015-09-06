//
//  VCTSocket.h
//  VCTSocketClient
//
//  Created by Vincent on 15/8/28.
//  Copyright (c) 2015年 Vincent. All rights reserved.
//

#ifndef __VCTSocketClient__VCTSocket__
#define __VCTSocketClient__VCTSocket__

#include <string>
#include "VCTBaseTypeDef.h"
#include <sys/select.h>

namespace VCT {
    
    class Socket {
    public:
        enum STATUS {
            NETWORK_ERROR = -1,
            CONNECT_TIMEOUT = -2,
            CONNECT_SUCCESS = 0
        };
        
        Socket(const char* ip,int port);
        
        ~Socket();
        
        // init a socket
        bool init();
        
        // connect a socket
        int connect();
        
        // send data
        int send(const char* buffer, int size);
        
        // recv data
        int recv(char* buffer, int size);
        
        // close socket
        void close();
        
        int select(timeval* timeout);
        
    private:

        int _sockfd;
        
        char _ip[16];
        
        int _port;
    };
}

#endif /* defined(__VCTSocketClient__VCTSocket__) */
