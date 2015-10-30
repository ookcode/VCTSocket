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
        //夹上宏不进行绑定
#ifdef COCOS2D_JAVASCRIPT
        Package(const char* buffer,int size);
        
        Package(UINT mainID,UINT assID,UINT handleID,const char *body,int bodySize);
#endif
        Package() = default;
        
        static Package* create(UINT maniID,UINT assID,UINT handleID,int bodySize);
        
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
        
        inline int getBodySize() {
            return getHead()->size - PACKAGE_HEAD_SIZE;
        }
        
        inline int getMainID() {
            return getHead()->mainID;
        }
        
        inline int getAssID() {
            return getHead()->assID;
        }
        
        inline int getHandleID() {
            return getHead()->handleID;
        }
        
        /******************************************
         js organize package
         *******************************************/
    public:
        void pushCHAR(const char* data,int size);
        
        char* popCHAR(int size);
        
        void pushUINT(UINT data);
        
        UINT popUINT();
        
        void pushINT(int data);
        
        int popINT();
        
        void pushLLONG(LLONG data);
        
        LLONG popLLONG();
        
        void pushULLONG(ULLONG data);
        
        ULLONG popULLONG();
        
        void pushBYTE(BYTE data);
        
        BYTE popBYTE();
        
    private:
        char _package[RECV_SIZE];
        int _offset = 0;
    };
}

#endif /* defined(__VCTSocketClient__VCTPackage__) */
