//
//  VCTBaseTypeDef.h
//  VCTSocketClient
//
//  Created by Vincent on 15/9/1.
//  Copyright (c) 2015年 Vincent. All rights reserved.
//

#ifndef VCTSocketClient_VCTBaseTypeDef_h
#define VCTSocketClient_VCTBaseTypeDef_h

#define RECV_SIZE 4096

#define DELETE(p)           do { delete (p); (p) = nullptr; } while(0)

typedef long long               LLONG;

typedef unsigned long long      ULLONG;

typedef int                     INT;

typedef unsigned int            UINT;

typedef unsigned char           BYTE;

#endif
