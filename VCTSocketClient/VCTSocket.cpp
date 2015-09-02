//
//  VCTSocket.cpp
//  VCTSocketClient
//
//  Created by Vincent on 15/8/28.
//  Copyright (c) 2015年 Vincent. All rights reserved.
//

#include "VCTSocket.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/select.h>

namespace VCT {
    Socket::Socket(const char* ip,int port) {
        strcpy(_ip, ip);
        _port = port;
    }
    
    Socket::~Socket() {
        
    }
    
    bool Socket::init() {
        // init socket
        _sockfd = socket(AF_INET, SOCK_STREAM, 0);
        if (_sockfd == -1) {
            perror("error open socket");
            close();
            return false;
        }
        return true;
    }
    
    int Socket::connect() {
        int status = NETWORK_ERROR;
        int flags;
        do {
            // init socket
            if (!init()) {
                break;
            }
            
            // init sockaddr_in
            sockaddr_in servaddr;
            memset(&servaddr, 0, sizeof(servaddr));
            servaddr.sin_family = AF_INET;
            servaddr.sin_port = htons(_port);
            
            // inet_aton 1 represent success , 0 represent fail
            if(inet_aton(_ip, &servaddr.sin_addr) == 0) {
                perror("error inet_pton");
            }
            
            // set non block mode
            flags = fcntl(_sockfd, F_GETFL, 0);
            fcntl(_sockfd, F_SETFL, flags | O_NONBLOCK);
            
            // connect
            int n = ::connect(_sockfd, (sockaddr*)&servaddr, sizeof(servaddr));
            if (n == -1 && errno != EINPROGRESS) {
                break;
            }
            
            if (n == 0) {
                // connect success at once (rare)
            }
            
            // set overtime second
            timeval tm = {10, 0};
            fd_set rset,wset;
            FD_ZERO(&rset);
            FD_SET(_sockfd, &rset);
            wset = rset;
            
            n = ::select(_sockfd + 1, &rset, &wset, nullptr, &tm);
            if (n == -1) {
                // network error
                perror("network error");
                break;
            }
            if (n == 0) {
                // time out
                status = CONNECT_TIMEOUT;
                perror("connect timeout");
                break;
            }
            
            if (FD_ISSET(_sockfd,&rset) || FD_ISSET(_sockfd,&wset)) {
                int error;
                socklen_t len = sizeof(error);
                if (getsockopt(_sockfd, SOL_SOCKET, SO_ERROR, &error, &len) < 0) {
                    perror("solaris pending error");
                    break;
                }
                if (error != 0) {
                    //network error, error == 0 represent connect successfully
                    break;
                }
            }else {
                perror("select error");
                break;
            }

            printf("socket connect successfully\n");
            status = CONNECT_SUCCESS;
            
        } while (0);
        
        //resume block
        fcntl(_sockfd, F_SETFL, flags);
        
        if (status != CONNECT_SUCCESS) close();
        
        return status;
    }
    
    int Socket::send(const char *buffer, int size) {
        //big package send series times
        int sentsize;
        int total = 0;
        while (total < size) {
            sentsize = (int)::send(_sockfd,buffer + total, size - total,0);
            if (sentsize == -1) {
                perror("error send to socket");
                close();
                return -1;
            }
            total += sentsize;
        }
        printf("socket send %d bytes successfully\n",total);
        return total;
    }
    
    int Socket::recv(char *buffer, int size) {
        int recvsize = (int)::recv(_sockfd, buffer, size, 0);
        if (recvsize == -1) {
            perror("error recv from socket");
        }else if (recvsize == 0) {
            printf("server close this socket\n");
        }
        printf("socket recv %d bytes successfully\n",recvsize);
        return recvsize;
    }
    
    void Socket::close() {
        ::close(_sockfd);
    }
}