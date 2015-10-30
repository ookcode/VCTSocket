#include "jsb_socketLogic.hpp"
#include "cocos2d_specifics.hpp"
#include "VCTSocketLogic.h"

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
JSClass  *jsb_VCT_SocketLogic_class;
JSObject *jsb_VCT_SocketLogic_prototype;

bool js_jsb_socketLogic_SocketLogic_openWithIp(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    VCT::SocketLogic* cobj = (VCT::SocketLogic *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_socketLogic_SocketLogic_openWithIp : Invalid Native Object");
    if (argc == 2) {
        const char* arg0;
        int arg1;
        std::string arg0_tmp; ok &= jsval_to_std_string(cx, args.get(0), &arg0_tmp); arg0 = arg0_tmp.c_str();
        ok &= jsval_to_int32(cx, args.get(1), (int32_t *)&arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_socketLogic_SocketLogic_openWithIp : Error processing arguments");
        cobj->openWithIp(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_jsb_socketLogic_SocketLogic_openWithIp : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_jsb_socketLogic_SocketLogic_addListener(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    VCT::SocketLogic* cobj = (VCT::SocketLogic *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_socketLogic_SocketLogic_addListener : Invalid Native Object");
    if (argc == 3) {
        unsigned int arg0;
        unsigned int arg1;
        std::function<bool (VCT::Package *)> arg2;
        ok &= jsval_to_uint32(cx, args.get(0), &arg0);
        ok &= jsval_to_uint32(cx, args.get(1), &arg1);
        do {
		    if(JS_TypeOfValue(cx, args.get(2)) == JSTYPE_FUNCTION)
		    {
		        std::shared_ptr<JSFunctionWrapper> func(new JSFunctionWrapper(cx, args.thisv().toObjectOrNull(), args.get(2)));
		        auto lambda = [=](VCT::Package* larg0) -> bool {
		            JSB_AUTOCOMPARTMENT_WITH_GLOBAL_OBJCET
		            jsval largv[1];
		            do {
		            if (larg0) {
		                js_proxy_t *jsProxy = js_get_or_create_proxy<VCT::Package>(cx, (VCT::Package*)larg0);
		                largv[0] = OBJECT_TO_JSVAL(jsProxy->obj);
		            } else {
		                largv[0] = JSVAL_NULL;
		            }
		        } while (0);
		            JS::RootedValue rval(cx);
		            bool succeed = func->invoke(1, &largv[0], &rval);
		            if (!succeed && JS_IsExceptionPending(cx)) {
		                JS_ReportPendingException(cx);
		            }
		            bool ret;
		            ret = JS::ToBoolean(rval);
		            return ret;
		        };
		        arg2 = lambda;
		    }
		    else
		    {
		        arg2 = nullptr;
		    }
		} while(0)
		;
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_socketLogic_SocketLogic_addListener : Error processing arguments");
        cobj->addListener(arg0, arg1, arg2);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_jsb_socketLogic_SocketLogic_addListener : wrong number of arguments: %d, was expecting %d", argc, 3);
    return false;
}
bool js_jsb_socketLogic_SocketLogic_sendPackage(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    VCT::SocketLogic* cobj = (VCT::SocketLogic *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_socketLogic_SocketLogic_sendPackage : Invalid Native Object");
    if (argc == 1) {
        VCT::Package* arg0;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (VCT::Package*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_socketLogic_SocketLogic_sendPackage : Error processing arguments");
        cobj->sendPackage(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_jsb_socketLogic_SocketLogic_sendPackage : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_jsb_socketLogic_SocketLogic_removeListener(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    VCT::SocketLogic* cobj = (VCT::SocketLogic *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_socketLogic_SocketLogic_removeListener : Invalid Native Object");
    if (argc == 2) {
        unsigned int arg0;
        unsigned int arg1;
        ok &= jsval_to_uint32(cx, args.get(0), &arg0);
        ok &= jsval_to_uint32(cx, args.get(1), &arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_socketLogic_SocketLogic_removeListener : Error processing arguments");
        cobj->removeListener(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_jsb_socketLogic_SocketLogic_removeListener : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_jsb_socketLogic_SocketLogic_close(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    VCT::SocketLogic* cobj = (VCT::SocketLogic *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_socketLogic_SocketLogic_close : Invalid Native Object");
    if (argc == 0) {
        cobj->close();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_jsb_socketLogic_SocketLogic_close : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_jsb_socketLogic_SocketLogic_getInstance(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        VCT::SocketLogic* ret = VCT::SocketLogic::getInstance();
        jsval jsret = JSVAL_NULL;
        do {
        if (ret) {
            js_proxy_t *jsProxy = js_get_or_create_proxy<VCT::SocketLogic>(cx, (VCT::SocketLogic*)ret);
            jsret = OBJECT_TO_JSVAL(jsProxy->obj);
        } else {
            jsret = JSVAL_NULL;
        }
    } while (0);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_jsb_socketLogic_SocketLogic_getInstance : wrong number of arguments");
    return false;
}


void js_VCT_SocketLogic_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (SocketLogic)", obj);
    js_proxy_t* nproxy;
    js_proxy_t* jsproxy;
    jsproxy = jsb_get_js_proxy(obj);
    if (jsproxy) {
        nproxy = jsb_get_native_proxy(jsproxy->ptr);

        VCT::SocketLogic *nobj = static_cast<VCT::SocketLogic *>(nproxy->ptr);
        if (nobj)
            delete nobj;
        
        jsb_remove_proxy(nproxy, jsproxy);
    }
}
void js_register_jsb_socketLogic_SocketLogic(JSContext *cx, JS::HandleObject global) {
    jsb_VCT_SocketLogic_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_VCT_SocketLogic_class->name = "SocketLogic";
    jsb_VCT_SocketLogic_class->addProperty = JS_PropertyStub;
    jsb_VCT_SocketLogic_class->delProperty = JS_DeletePropertyStub;
    jsb_VCT_SocketLogic_class->getProperty = JS_PropertyStub;
    jsb_VCT_SocketLogic_class->setProperty = JS_StrictPropertyStub;
    jsb_VCT_SocketLogic_class->enumerate = JS_EnumerateStub;
    jsb_VCT_SocketLogic_class->resolve = JS_ResolveStub;
    jsb_VCT_SocketLogic_class->convert = JS_ConvertStub;
    jsb_VCT_SocketLogic_class->finalize = js_VCT_SocketLogic_finalize;
    jsb_VCT_SocketLogic_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("openWithIp", js_jsb_socketLogic_SocketLogic_openWithIp, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("addListener", js_jsb_socketLogic_SocketLogic_addListener, 3, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("sendPackage", js_jsb_socketLogic_SocketLogic_sendPackage, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("removeListener", js_jsb_socketLogic_SocketLogic_removeListener, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("close", js_jsb_socketLogic_SocketLogic_close, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("getInstance", js_jsb_socketLogic_SocketLogic_getInstance, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_VCT_SocketLogic_prototype = JS_InitClass(
        cx, global,
        JS::NullPtr(), // parent proto
        jsb_VCT_SocketLogic_class,
        dummy_constructor<VCT::SocketLogic>, 0, // no constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "SocketLogic", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<VCT::SocketLogic> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_VCT_SocketLogic_class;
        p->proto = jsb_VCT_SocketLogic_prototype;
        p->parentProto = NULL;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

void register_all_jsb_socketLogic(JSContext* cx, JS::HandleObject obj) {
    // Get the ns
    JS::RootedObject ns(cx);
    get_or_create_js_obj(cx, obj, "VCT", &ns);

    js_register_jsb_socketLogic_SocketLogic(cx, ns);
}

