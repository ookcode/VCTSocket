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
    
#define BASE_PACKAGE_MAINID 0
    
#define NET_ERROR_PACKAGE           Package(BASE_PACKAGE_MAINID, ass_net_error, 0, nullptr, 0)
#define NET_TIMEOUT_PACKAGE         Package(BASE_PACKAGE_MAINID, ass_net_timeout, 0, nullptr, 0)
#define HEART_BEAT_PACKAGE          Package(BASE_PACKAGE_MAINID, ass_heart_beat, 0, nullptr, 0)
#define SERVER_CLOSE_PACKAGE        Package(BASE_PACKAGE_MAINID, ass_server_close, 0, nullptr, 0)
    
    enum BASE_PACKAGE_ASSID {
        ass_heart_beat = 0,
        ass_net_error = 1,
        ass_net_timeout = 2,
        ass_server_close = 3
    };
    
    // head package
    struct PACKAGE_HEAD {
        UINT size;      // total package size
        UINT mainID;
        UINT assID;
        UINT handleID;
    };
    
    static const UINT PACKAGE_HEAD_SIZE = sizeof(PACKAGE_HEAD);

}

#endif
