#include "jsb_package.hpp"
#include "cocos2d_specifics.hpp"
#include "VCTPackage.h"

template<class T>
static bool dummy_constructor(JSContext *cx, uint32_t argc, jsval *vp) {
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedValue initializing(cx);
    bool isNewValid = true;
    if (isNewValid)
    {
        TypeTest<T> t;
        js_type_class_t *typeClass = nullptr;
        std::string typeName = t.s_name();
        auto typeMapIter = _js_global_type_map.find(typeName);
        CCASSERT(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
        typeClass = typeMapIter->second;
        CCASSERT(typeClass, "The value is null.");

        JS::RootedObject proto(cx, typeClass->proto.get());
        JS::RootedObject parent(cx, typeClass->parentProto.get());
        JS::RootedObject _tmp(cx, JS_NewObject(cx, typeClass->jsclass, proto, parent));
        
        T* cobj = new T();
        js_proxy_t *pp = jsb_new_proxy(cobj, _tmp);
        AddObjectRoot(cx, &pp->obj);
        args.rval().set(OBJECT_TO_JSVAL(_tmp));
        return true;
    }

    return false;
}

static bool empty_constructor(JSContext *cx, uint32_t argc, jsval *vp) {
    return false;
}

static bool js_is_native_obj(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    args.rval().setBoolean(true);
    return true;    
}
JSClass  *jsb_VCT_Package_class;
JSObject *jsb_VCT_Package_prototype;

bool js_jsb_package_Package_getAssID(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    VCT::Package* cobj = (VCT::Package *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_package_Package_getAssID : Invalid Native Object");
    if (argc == 0) {
        int ret = cobj->getAssID();
        jsval jsret = JSVAL_NULL;
        jsret = int32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_package_Package_getAssID : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_jsb_package_Package_popBYTE(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    VCT::Package* cobj = (VCT::Package *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_package_Package_popBYTE : Invalid Native Object");
    if (argc == 0) {
        uint16_t ret = cobj->popBYTE();
        jsval jsret = JSVAL_NULL;
        jsret = uint32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_package_Package_popBYTE : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_jsb_package_Package_pushBYTE(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    VCT::Package* cobj = (VCT::Package *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_package_Package_pushBYTE : Invalid Native Object");
    if (argc == 1) {
        uint16_t arg0;
        ok &= jsval_to_uint16(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_package_Package_pushBYTE : Error processing arguments");
        cobj->pushBYTE(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_jsb_package_Package_pushBYTE : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_jsb_package_Package_popULLONG(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    VCT::Package* cobj = (VCT::Package *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_package_Package_popULLONG : Invalid Native Object");
    if (argc == 0) {
        unsigned long long ret = cobj->popULLONG();
        jsval jsret = JSVAL_NULL;
        #pragma warning NO CONVERSION FROM NATIVE FOR unsigned long long;
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_package_Package_popULLONG : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_jsb_package_Package_pushCHAR(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    VCT::Package* cobj = (VCT::Package *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_package_Package_pushCHAR : Invalid Native Object");
    if (argc == 2) {
        const char* arg0 = nullptr;
        int arg1 = 0;
        std::string arg0_tmp; ok &= jsval_to_std_string(cx, args.get(0), &arg0_tmp); arg0 = arg0_tmp.c_str();
        ok &= jsval_to_int32(cx, args.get(1), (int32_t *)&arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_package_Package_pushCHAR : Error processing arguments");
        cobj->pushCHAR(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_jsb_package_Package_pushCHAR : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_jsb_package_Package_popUINT(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    VCT::Package* cobj = (VCT::Package *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_package_Package_popUINT : Invalid Native Object");
    if (argc == 0) {
        unsigned int ret = cobj->popUINT();
        jsval jsret = JSVAL_NULL;
        jsret = uint32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_package_Package_popUINT : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_jsb_package_Package_pushUINT(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    VCT::Package* cobj = (VCT::Package *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_package_Package_pushUINT : Invalid Native Object");
    if (argc == 1) {
        unsigned int arg0 = 0;
        ok &= jsval_to_uint32(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_package_Package_pushUINT : Error processing arguments");
        cobj->pushUINT(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_jsb_package_Package_pushUINT : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_jsb_package_Package_getHead(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    VCT::Package* cobj = (VCT::Package *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_package_Package_getHead : Invalid Native Object");
    if (argc == 0) {
        VCT::PACKAGE_HEAD* ret = cobj->getHead();
        jsval jsret = JSVAL_NULL;
        #pragma warning NO CONVERSION FROM NATIVE FOR PACKAGE_HEAD*;
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_package_Package_getHead : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_jsb_package_Package_getHandleID(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    VCT::Package* cobj = (VCT::Package *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_package_Package_getHandleID : Invalid Native Object");
    if (argc == 0) {
        int ret = cobj->getHandleID();
        jsval jsret = JSVAL_NULL;
        jsret = int32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_package_Package_getHandleID : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_jsb_package_Package_getMainID(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    VCT::Package* cobj = (VCT::Package *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_package_Package_getMainID : Invalid Native Object");
    if (argc == 0) {
        int ret = cobj->getMainID();
        jsval jsret = JSVAL_NULL;
        jsret = int32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_package_Package_getMainID : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_jsb_package_Package_getSize(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    VCT::Package* cobj = (VCT::Package *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_package_Package_getSize : Invalid Native Object");
    if (argc == 0) {
        int ret = cobj->getSize();
        jsval jsret = JSVAL_NULL;
        jsret = int32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_package_Package_getSize : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_jsb_package_Package_pushINT(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    VCT::Package* cobj = (VCT::Package *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_package_Package_pushINT : Invalid Native Object");
    if (argc == 1) {
        int arg0 = 0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_package_Package_pushINT : Error processing arguments");
        cobj->pushINT(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_jsb_package_Package_pushINT : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_jsb_package_Package_popCHAR(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    VCT::Package* cobj = (VCT::Package *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_package_Package_popCHAR : Invalid Native Object");
    if (argc == 1) {
        int arg0 = 0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_package_Package_popCHAR : Error processing arguments");
        char* ret = cobj->popCHAR(arg0);
        jsval jsret = JSVAL_NULL;
        jsret = c_string_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_package_Package_popCHAR : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_jsb_package_Package_pushULLONG(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    VCT::Package* cobj = (VCT::Package *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_package_Package_pushULLONG : Invalid Native Object");
    if (argc == 1) {
        unsigned long long arg0 = 0;
        #pragma warning NO CONVERSION TO NATIVE FOR unsigned long long
		ok = false;
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_package_Package_pushULLONG : Error processing arguments");
        cobj->pushULLONG(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_jsb_package_Package_pushULLONG : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_jsb_package_Package_getPackage(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    VCT::Package* cobj = (VCT::Package *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_package_Package_getPackage : Invalid Native Object");
    if (argc == 0) {
        const char* ret = cobj->getPackage();
        jsval jsret = JSVAL_NULL;
        jsret = c_string_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_package_Package_getPackage : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_jsb_package_Package_getBodySize(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    VCT::Package* cobj = (VCT::Package *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_package_Package_getBodySize : Invalid Native Object");
    if (argc == 0) {
        int ret = cobj->getBodySize();
        jsval jsret = JSVAL_NULL;
        jsret = int32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_package_Package_getBodySize : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_jsb_package_Package_pushLLONG(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    VCT::Package* cobj = (VCT::Package *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_package_Package_pushLLONG : Invalid Native Object");
    if (argc == 1) {
        long long arg0 = 0;
        ok &= jsval_to_long_long(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_package_Package_pushLLONG : Error processing arguments");
        cobj->pushLLONG(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_jsb_package_Package_pushLLONG : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_jsb_package_Package_popLLONG(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    VCT::Package* cobj = (VCT::Package *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_package_Package_popLLONG : Invalid Native Object");
    if (argc == 0) {
        long long ret = cobj->popLLONG();
        jsval jsret = JSVAL_NULL;
        jsret = long_long_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_package_Package_popLLONG : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_jsb_package_Package_popINT(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    VCT::Package* cobj = (VCT::Package *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_package_Package_popINT : Invalid Native Object");
    if (argc == 0) {
        int ret = cobj->popINT();
        jsval jsret = JSVAL_NULL;
        jsret = int32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_package_Package_popINT : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_jsb_package_Package_getBody(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    VCT::Package* cobj = (VCT::Package *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_package_Package_getBody : Invalid Native Object");
    if (argc == 0) {
        const void* ret = cobj->getBody();
        jsval jsret = JSVAL_NULL;
        #pragma warning NO CONVERSION FROM NATIVE FOR void*;
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_package_Package_getBody : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_jsb_package_Package_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 4) {
        unsigned int arg0 = 0;
        unsigned int arg1 = 0;
        unsigned int arg2 = 0;
        int arg3 = 0;
        ok &= jsval_to_uint32(cx, args.get(0), &arg0);
        ok &= jsval_to_uint32(cx, args.get(1), &arg1);
        ok &= jsval_to_uint32(cx, args.get(2), &arg2);
        ok &= jsval_to_int32(cx, args.get(3), (int32_t *)&arg3);
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_package_Package_create : Error processing arguments");
        VCT::Package* ret = VCT::Package::create(arg0, arg1, arg2, arg3);
        jsval jsret = JSVAL_NULL;
        do {
        if (ret) {
            js_proxy_t *jsProxy = js_get_or_create_proxy<VCT::Package>(cx, (VCT::Package*)ret);
            jsret = OBJECT_TO_JSVAL(jsProxy->obj);
        } else {
            jsret = JSVAL_NULL;
        }
    } while (0);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_jsb_package_Package_create : wrong number of arguments");
    return false;
}

bool js_jsb_package_Package_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    VCT::Package* cobj = new (std::nothrow) VCT::Package();
    TypeTest<VCT::Package> t;
    js_type_class_t *typeClass = nullptr;
    std::string typeName = t.s_name();
    auto typeMapIter = _js_global_type_map.find(typeName);
    CCASSERT(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
    typeClass = typeMapIter->second;
    CCASSERT(typeClass, "The value is null.");
    JS::RootedObject proto(cx, typeClass->proto.get());
    JS::RootedObject parent(cx, typeClass->parentProto.get());
    JS::RootedObject obj(cx, JS_NewObject(cx, typeClass->jsclass, proto, parent));
    args.rval().set(OBJECT_TO_JSVAL(obj));
    // link the native object with the javascript object
    js_proxy_t* p = jsb_new_proxy(cobj, obj);
    if (JS_HasProperty(cx, obj, "_ctor", &ok) && ok)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", args);
    return true;
}

void js_VCT_Package_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (Package)", obj);
    js_proxy_t* nproxy;
    js_proxy_t* jsproxy;
    jsproxy = jsb_get_js_proxy(obj);
    if (jsproxy) {
        VCT::Package *nobj = static_cast<VCT::Package *>(jsproxy->ptr);
        nproxy = jsb_get_native_proxy(jsproxy->ptr);

        if (nobj) {
            jsb_remove_proxy(nproxy, jsproxy);
            delete nobj;
        }
        else jsb_remove_proxy(nullptr, jsproxy);
    }
}
void js_register_jsb_package_Package(JSContext *cx, JS::HandleObject global) {
    jsb_VCT_Package_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_VCT_Package_class->name = "Package";
    jsb_VCT_Package_class->addProperty = JS_PropertyStub;
    jsb_VCT_Package_class->delProperty = JS_DeletePropertyStub;
    jsb_VCT_Package_class->getProperty = JS_PropertyStub;
    jsb_VCT_Package_class->setProperty = JS_StrictPropertyStub;
    jsb_VCT_Package_class->enumerate = JS_EnumerateStub;
    jsb_VCT_Package_class->resolve = JS_ResolveStub;
    jsb_VCT_Package_class->convert = JS_ConvertStub;
    jsb_VCT_Package_class->finalize = js_VCT_Package_finalize;
    jsb_VCT_Package_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("getAssID", js_jsb_package_Package_getAssID, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("popBYTE", js_jsb_package_Package_popBYTE, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("pushBYTE", js_jsb_package_Package_pushBYTE, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("popULLONG", js_jsb_package_Package_popULLONG, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("pushCHAR", js_jsb_package_Package_pushCHAR, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("popUINT", js_jsb_package_Package_popUINT, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("pushUINT", js_jsb_package_Package_pushUINT, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getHead", js_jsb_package_Package_getHead, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getHandleID", js_jsb_package_Package_getHandleID, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getMainID", js_jsb_package_Package_getMainID, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getSize", js_jsb_package_Package_getSize, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("pushINT", js_jsb_package_Package_pushINT, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("popCHAR", js_jsb_package_Package_popCHAR, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("pushULLONG", js_jsb_package_Package_pushULLONG, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getPackage", js_jsb_package_Package_getPackage, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getBodySize", js_jsb_package_Package_getBodySize, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("pushLLONG", js_jsb_package_Package_pushLLONG, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("popLLONG", js_jsb_package_Package_popLLONG, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("popINT", js_jsb_package_Package_popINT, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getBody", js_jsb_package_Package_getBody, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("create", js_jsb_package_Package_create, 4, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_VCT_Package_prototype = JS_InitClass(
        cx, global,
        JS::NullPtr(), // parent proto
        jsb_VCT_Package_class,
        js_jsb_package_Package_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "Package", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<VCT::Package> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_VCT_Package_class;
        p->proto = jsb_VCT_Package_prototype;
        p->parentProto = NULL;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

void register_all_jsb_package(JSContext* cx, JS::HandleObject obj) {
    // Get the ns
    JS::RootedObject ns(cx);
    get_or_create_js_obj(cx, obj, "VCT", &ns);

    js_register_jsb_package_Package(cx, ns);
}

