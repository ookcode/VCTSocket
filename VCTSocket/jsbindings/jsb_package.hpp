#include "base/ccConfig.h"
#ifndef __jsb_package_h__
#define __jsb_package_h__

#include "jsapi.h"
#include "jsfriendapi.h"

extern JSClass  *jsb_VCT_Package_class;
extern JSObject *jsb_VCT_Package_prototype;

bool js_jsb_package_Package_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_jsb_package_Package_finalize(JSContext *cx, JSObject *obj);
void js_register_jsb_package_Package(JSContext *cx, JS::HandleObject global);
void register_all_jsb_package(JSContext* cx, JS::HandleObject obj);
bool js_jsb_package_Package_getAssID(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_package_Package_popBYTE(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_package_Package_pushBYTE(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_package_Package_popULLONG(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_package_Package_pushCHAR(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_package_Package_popUINT(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_package_Package_pushUINT(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_package_Package_getHead(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_package_Package_getHandleID(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_package_Package_getMainID(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_package_Package_getSize(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_package_Package_pushINT(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_package_Package_popCHAR(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_package_Package_pushULLONG(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_package_Package_getPackage(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_package_Package_getBodySize(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_package_Package_pushLLONG(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_package_Package_popLLONG(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_package_Package_popINT(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_package_Package_getBody(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_package_Package_create(JSContext *cx, uint32_t argc, jsval *vp);
bool js_jsb_package_Package_Package(JSContext *cx, uint32_t argc, jsval *vp);

#endif // __jsb_package_h__
