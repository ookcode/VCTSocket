//
//  VCTPackage.cpp
//  VCTSocketClient
//
//  Created by Vincent on 15/9/1.
//  Copyright (c) 2015年 Vincent. All rights reserved.
//

#include "VCTPackage.h"

namespace VCT {

    Package::Package(const char* buffer,int size) {
        memcpy(_package, buffer, size);
    }
    
    Package::Package(UINT mainID, UINT assID, UINT handleID, const void *body, int bodySize) {
        
        PACKAGE_HEAD head;
        head.mainID = mainID;
        head.assID = assID;
        head.handleID = handleID;
        head.size = bodySize + PACKAGE_HEAD_SIZE;
        
        memcpy(_package, &head, PACKAGE_HEAD_SIZE);
        memcpy(_package + PACKAGE_HEAD_SIZE, body, bodySize);
    }
    
    Package::~Package() {
        
    }
}