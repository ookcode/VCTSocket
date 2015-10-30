//
//  VCTPackage.cpp
//  VCTSocketClient
//
//  Created by Vincent on 15/9/1.
//  Copyright (c) 2015年 Vincent. All rights reserved.
//

#include "VCTPackage.h"

namespace VCT {
    //夹上宏不进行绑定
#ifdef COCOS2D_JAVASCRIPT
    Package::Package(const char* buffer,int size) {
        memcpy(_package, buffer, size);
    }

    Package::Package(UINT mainID, UINT assID, UINT handleID,const char *body, int bodySize) {

        PACKAGE_HEAD head;
        head.mainID = mainID;
        head.assID = assID;
        head.handleID = handleID;
        head.size = bodySize + PACKAGE_HEAD_SIZE;
        memcpy(_package, &head, PACKAGE_HEAD_SIZE);
        if (body) {
            memcpy(_package + PACKAGE_HEAD_SIZE, body, bodySize);
        }
    }
#endif
    
    Package* Package::create(UINT maniID,UINT assID,UINT handleID,int bodySize) {
        Package *pack = new Package(maniID,assID,handleID,nullptr,bodySize);
        return pack;
    }

    /******************************************
     
     js organize package
     
     *******************************************/
    void Package::pushCHAR(const char* data,int size) {
        char *temp = new char[size];
        memset(temp, 0, size);//清零
        memcpy(temp, data, strlen(data));//复制
        memcpy(_package + PACKAGE_HEAD_SIZE + _offset, temp, size);//导入
        _offset += size;
        delete [] temp;
    }
    
    char* Package::popCHAR(int size) {
        char *data = _package + PACKAGE_HEAD_SIZE + _offset;
        _offset += size;
        return data;
    }
    
    void Package::pushUINT(UINT data) {
        memcpy(_package + PACKAGE_HEAD_SIZE + _offset, &data, sizeof(UINT));
        _offset += sizeof(UINT);
    }
    
    UINT Package::popUINT() {
        UINT *data = (UINT *)(_package + PACKAGE_HEAD_SIZE + _offset);
        _offset += sizeof(UINT);
        return *data;
    }
    
    void Package::pushINT(int data) {
        memcpy(_package + PACKAGE_HEAD_SIZE + _offset, &data, sizeof(int));
        _offset += sizeof(int);
    }
    
    int Package::popINT() {
        int *data = (int *)(_package + PACKAGE_HEAD_SIZE + _offset);
        _offset += sizeof(int);
        return *data;
    }
    
    void Package::pushLLONG(LLONG data) {
        memcpy(_package + PACKAGE_HEAD_SIZE + _offset, &data, sizeof(LLONG));
        _offset += sizeof(LLONG);
    }
    
    LLONG Package::popLLONG() {
        LLONG *data = (LLONG *)(_package + PACKAGE_HEAD_SIZE + _offset);
        _offset += sizeof(LLONG);
        return *data;
    }
    
    void Package::pushULLONG(ULLONG data) {
        memcpy(_package + PACKAGE_HEAD_SIZE + _offset, &data, sizeof(ULLONG));
        _offset += sizeof(ULLONG);
    }
    
    ULLONG Package::popULLONG() {
        ULLONG *data = (ULLONG *)(_package + PACKAGE_HEAD_SIZE + _offset);
        _offset += sizeof(ULLONG);
        return *data;
    }
    
    void Package::pushBYTE(BYTE data) {
        memcpy(_package + PACKAGE_HEAD_SIZE + _offset, &data, sizeof(BYTE));
        _offset += sizeof(BYTE);
    }
    
    BYTE Package::popBYTE() {
        BYTE *data = (BYTE *)(_package + PACKAGE_HEAD_SIZE + _offset);
        _offset += sizeof(BYTE);
        return *data;
    }
}