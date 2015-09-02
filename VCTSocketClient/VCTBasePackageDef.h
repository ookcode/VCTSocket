//
//  VCTBasePackageDef.h
//  VCTSocketClient
//
//  Created by Vincent on 15/9/1.
//  Copyright (c) 2015年 Vincent. All rights reserved.
//

#ifndef VCTSocketClient_VCTBasePackageDef_h
#define VCTSocketClient_VCTBasePackageDef_h

#include "VCTBaseTypeDef.h"

namespace VCT {
    
#define RECV_SIZE 4096

    // package head struct
    struct PACKAGE_HEAD {
        UINT size;      // total package size
        UINT firstID;
        UINT secondID;
        UINT thirdID;
    };
    static const UINT PACKAGE_HEAD_SIZE = sizeof(PACKAGE_HEAD);
}

#endif
