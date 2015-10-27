//
//  main.cpp
//  VCTSocketClient
//
//  Created by Vincent on 15/8/28.
//  Copyright (c) 2015年 Vincent. All rights reserved.
//

#include <iostream>
#include "VCTSocketLogic.h"
using namespace VCT;

int main(int argc, const char * argv[]) {
    printf("enter some command and have fun :)\n");
    while (true) {
        char input[128];
        scanf("%s",input);
        if (strcmp(input, "connect") == 0) {
            SocketLogic::getInstance()->openWithIp("127.0.0.1", 8887);
            continue;
        }
        if (strcmp(input, "close") == 0) {
            SocketLogic::getInstance()->close();
            continue;
        }
    }
    return 0;
}
