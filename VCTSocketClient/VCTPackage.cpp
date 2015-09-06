//
//  VCTPackage.cpp
//  VCTSocketClient
//
//  Created by Vincent on 15/9/1.
//  Copyright (c) 2015年 Vincent. All rights reserved.
//

#include "VCTPackage.h"

namespace VCT {

    Package::Package(TYPE type,const char* buffer,int size) {
        _type = type;
        memcpy(_package, buffer, size);
    }
    
    Package::Package(TYPE type,UINT firstID, UINT secondID, UINT thirdID, const void *body, int bodySize) {
        
        _type = type;
        
        PACKAGE_HEAD head;
        head.firstID = firstID;
        head.secondID = secondID;
        head.thirdID = thirdID;
        head.size = bodySize + PACKAGE_HEAD_SIZE;
        
        memcpy(_package, &head, PACKAGE_HEAD_SIZE);
        memcpy(_package + PACKAGE_HEAD_SIZE, body, bodySize);
    }
    
    Package::~Package() {
        
    }
}