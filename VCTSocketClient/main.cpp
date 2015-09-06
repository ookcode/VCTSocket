//
//  main.cpp
//  VCTSocketClient
//
//  Created by Vincent on 15/8/28.
//  Copyright (c) 2015年 Vincent. All rights reserved.
//

#include <iostream>
#include "VCTSocketThread.h"
#include "VCTPackage.h"
#include <unistd.h>
using namespace VCT;

struct TEST
{
    char username[12];
    UINT userid;
};

class MainUI : public SocketThread::Delegate {
public:
    MainUI() {
        printf("enter some command and have fun :)\n");
    }
    
    ~MainUI() {
        _thread->destory();
        _thread = nullptr;
    }
    
    void connect() {
        _thread = SocketThread::create(this);
        _thread->openWithIp("127.0.0.1", 8887);
    }
    
    void close() {
        _thread->close();
    }
    
private:
    SocketThread *_thread;
    
    virtual void onConnected() override {
        printf("onConnected\n");
        
    }
    
    virtual void onDisConnected() override {
        printf("onDisConnected\n");
    }
    
    virtual void recvPackage(Package *package) override {
        printf("recvPackage\n");
    }
};

int main(int argc, const char * argv[]) {
    
    MainUI mainUI;
    while (true) {
        char input[128];
        scanf("%s",input);
        if (strcmp(input, "connect") == 0) {
            mainUI.connect();
            continue;
        }
        if (strcmp(input, "close") == 0) {
            mainUI.close();
            continue;
        }
    }
    return 0;
}
