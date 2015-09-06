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
        
        enum TYPE{
            SEND,
            RECV,
            ERROR
        };
        
        Package(TYPE type,const char* buffer,int size);
        
        Package(TYPE type,UINT firstID,UINT secondID,UINT thirdID,const void *body,int bodySize);
        
        ~Package();
        
        inline const char* getPackage() {
            return _package;
        }
        
        inline PACKAGE_HEAD* getHead() {
            return (PACKAGE_HEAD *)_package;
        }
        
        inline const void* getBody() {
            return _package + PACKAGE_HEAD_SIZE;
        }
        
        inline int getSize() {
            return getHead()->size;
        }
        
        inline TYPE getType() {
            return _type;
        }
        
    private:
        TYPE _type;
        char _package[RECV_SIZE];
    };
}

#endif /* defined(__VCTSocketClient__VCTPackage__) */
