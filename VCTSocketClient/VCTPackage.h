//
//  VCTPackage.h
//  VCTSocketClient
//
//  Created by Vincent on 15/9/1.
//  Copyright (c) 2015年 Vincent. All rights reserved.
//

#ifndef __VCTSocketClient__VCTPackage__
#define __VCTSocketClient__VCTPackage__

#include <memory>
#include "VCTBasePackageDef.h"

namespace VCT {
    
    class Package {
    public:
        
        Package();
        
        Package(const PACKAGE_HEAD *head,const void* body,int bodySize);
        
        Package(UINT firstID,UINT secondID,UINT thirdID,const void *body,int bodySize);
        
        ~Package();
        
        inline const char* getPackage() {
            return _package;
        }
        
        inline PACKAGE_HEAD* getHead() {
            return &_head;
        }
        
        inline const void* getBody() {
            return _package + PACKAGE_HEAD_SIZE;
        }
        
        inline int getSize() {
            return _head.size;
        }
        
        void encode(const PACKAGE_HEAD *head,const void* body,int bodySize);

        void encode(UINT firstID,UINT secondID,UINT thirdID,const void *body,int bodySize);
        
    private:
        
        PACKAGE_HEAD _head;
        char _package[RECV_SIZE];
    };
}

#endif /* defined(__VCTSocketClient__VCTPackage__) */
