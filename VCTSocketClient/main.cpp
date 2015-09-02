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

using namespace VCT;

struct TEST
{
    char username[12];
    UINT userid;
};

class MainUI : public SocketThread::Delegate {
public:
    MainUI() {
        SocketThread st(this);
        st.openWithIp("127.0.0.1", 8887);
        
        if (st.isConnected()) {
            TEST t;
            strcpy(t.username, "vincent");
            t.userid = 102;
            
            Package package(1,2,3,&t,sizeof(t));
            st.sendPackage(&package);
        }
        
    }
private:
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
        ;
    }
    return 0;
}
