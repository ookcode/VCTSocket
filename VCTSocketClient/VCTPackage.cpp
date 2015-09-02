//
//  VCTPackage.cpp
//  VCTSocketClient
//
//  Created by Vincent on 15/9/1.
//  Copyright (c) 2015年 Vincent. All rights reserved.
//

#include "VCTPackage.h"

namespace VCT {
    Package::Package() {
        memcpy(&_head, 0, PACKAGE_HEAD_SIZE);
        memcpy(_package, 0, sizeof(_package));
    }
    
    Package::Package(const PACKAGE_HEAD *head, const void *body, int bodySize) {
        _head = *head;
        memcpy(_package, &_head, PACKAGE_HEAD_SIZE);
        memcpy(_package + PACKAGE_HEAD_SIZE, body, bodySize);
    }
    
    Package::Package(UINT firstID, UINT secondID, UINT thirdID, const void *body, int bodySize) {
        _head.firstID = firstID;
        _head.secondID = secondID;
        _head.thirdID = thirdID;
        _head.size = bodySize + PACKAGE_HEAD_SIZE;
        memcpy(_package, &_head, PACKAGE_HEAD_SIZE);
        memcpy(_package + PACKAGE_HEAD_SIZE, body, bodySize);
    }
    
    Package::~Package() {
        
    }
}