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

        Package(const char* buffer,int size);
        
        Package(UINT mainID,UINT assID,UINT handleID,const void *body,int bodySize);
        
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
        
        inline int getMainID() {
            return getHead()->mainID;
        }
        
        inline int getAssID() {
            return getHead()->assID;
        }
        
    private:
        char _package[RECV_SIZE];
    };
}

#endif /* defined(__VCTSocketClient__VCTPackage__) */
