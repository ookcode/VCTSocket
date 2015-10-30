#include "base/ccConfig.h"
#ifndef __jsb_socketLogic_h__
#define __jsb_socketLogic_h__

#include "jsapi.h"
#include "jsfriendapi.h"

extern JSClass  *jsb_VCT_SocketLogic_class;
extern JSObject *jsb_VCT_SocketLogic_prototype;

bool js_jsb_socketLogic_SocketLogic_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_jsb_socketLogic_SocketLogic_finalize(JSContext *cx, JSObject *obj);
void js_register_jsb_socketLogic_SocketLogic(JSContext *cx, JS::HandleObject global);
void register_all_jsb_socketLogic(JSContext* cx, JS::HandleObject obj);
bool js_jsb_socketLogic_SocketLogic_openWithIp(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_socketLogic_SocketLogic_addListener(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_socketLogic_SocketLogic_sendPackage(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_socketLogic_SocketLogic_removeListener(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_socketLogic_SocketLogic_close(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_socketLogic_SocketLogic_getInstance(JSContext *cx, uint32_t argc, jsval *vp);

#endif // __jsb_socketLogic_h__
