#include <core/module/hook_java.h>
#include <innercore_callbacks.h>
#include <logger.h>

#include <hook.h>
#include <symbol.h>
#include <stl/string>
#include <functional>
#define stl std::__ndk1

jclass HookJava::HOOK;
jclass HookJava::DATA;
jclass HookJava::OBJECT;
jclass HookJava::INIT;
jmethodID HookJava::ID;
jmethodID HookJava::ID_INTAS;
jmethodID HookJava::ID_FLOATAS;
jmethodID HookJava::ID_LongAS;
jobject HookJava::obj;
std::map<std::string, jstring> HookJava::cache;

std::vector<Hook*> HookJava::getHooks(JNIEnv* env){
    const jmethodID getJsons = env->GetStaticMethodID(HookJava::HOOK, "getJsons", "()[Lcom/core/api/module/JsonData;");
    const jmethodID getSymbol = env->GetMethodID(HookJava::DATA, "getSymbol", "()Ljava/lang/String;");
    const jmethodID getCallback = env->GetMethodID(HookJava::DATA, "getCallback", "()Ljava/lang/String;");
    const jmethodID getPriority = env->GetMethodID(HookJava::DATA, "getPriority", "()Ljava/lang/String;");
    const jmethodID getReturn = env->GetMethodID(HookJava::DATA, "getReturn", "()Ljava/lang/String;");
    const jmethodID getLib = env->GetMethodID(HookJava::DATA, "getLib", "()Ljava/lang/String;");
    const jmethodID getArgs = env->GetMethodID(HookJava::DATA, "getArgs", "()[Ljava/lang/String;");
	const jobjectArray array = (jobjectArray) env->CallStaticObjectMethod(HookJava::HOOK, getJsons);

    std::vector<Hook*> hooks;
    for(int i=0;i<env->GetArrayLength(array);i++) {
        jobject json = env->GetObjectArrayElement(array, i);
        jstring symbol = (jstring) env->CallObjectMethod(json, getSymbol);
        jstring callback = (jstring) env->CallObjectMethod(json, getCallback);
        jstring priority = (jstring) env->CallObjectMethod(json, getPriority);
        jstring returnType = (jstring) env->CallObjectMethod(json, getReturn);
        jstring lib = (jstring) env->CallObjectMethod(json, getLib);
        jobjectArray arr = (jobjectArray) env->CallObjectMethod(json, getArgs);
        std::vector<std::string> args;
        for(int j=0;j<env->GetArrayLength(arr);j++) {
            args.push_back(JavaClass::toString(env,(jstring) env->GetObjectArrayElement(arr, j)));
        }
        hooks.push_back(new Hook(
            JavaClass::toString(env, symbol),
            JavaClass::toString(env, callback),
            JavaClass::toString(env, priority),
            JavaClass::toString(env, returnType),
            args,
            JavaClass::toString(env, lib)
        ));
    }
    return hooks;
}

std::vector<Init*> HookJava::getInits(JNIEnv* env){
    const jmethodID getInits = env->GetStaticMethodID(HookJava::HOOK, "getInits", "()[Lcom/core/api/module/InitData;");
    const jmethodID getName = env->GetMethodID(HookJava::INIT, "getName", "()Ljava/lang/String;");
    const jmethodID getLib = env->GetMethodID(HookJava::INIT, "getLib", "()Ljava/lang/String;");
    const jobjectArray array = (jobjectArray) env->CallStaticObjectMethod(HookJava::HOOK, getInits);

    std::vector<Init*> result;
    for(int i=0;i<env->GetArrayLength(array);i++){
        jobject object = env->GetObjectArrayElement(array, i);
        result.push_back(new Init(JavaClass::toString(env, (jstring) env->CallObjectMethod(object, getName)), JavaClass::toString(env, (jstring) env->CallObjectMethod(object, getLib))));
    }
    return result;
}

class Controller {
    private:
        HookManager::CallbackController* controller;
        bool isResultV;
        jobject result;
    public:
        Controller(HookManager::CallbackController* controller){
            this->controller = controller;
            isResultV = false;
        }
        void end(JNIEnv* env){
            env->DeleteGlobalRef(result);
        }
        void replace(){
            controller->replace();
        }
        bool isResult(){
            return isResultV;
        }
        void setIsResult(bool v){
            isResultV = v;
        }
        void setResult(jobject v){
            result = v;
        }
        jobject getResultHook(){
            return result;
        }
};

#include <core/module/NativeAPI.h>

inline void registerParameter(JNIEnv* env, void* paramter, jobjectArray& array, int i, std::string type){
    if(type == "ptr"){
        env->SetObjectArrayElement(array, i, NativeAPI::createHookParameter(env, (jlong) paramter, HookJava::getJavaString(env, type)));
    }else if(type == "int"){
        env->SetObjectArrayElement(array, i, NativeAPI::createHookParameter(env, (jint) ((int)paramter), HookJava::getJavaString(env, type)));
    }else if(type == "bool"){
        env->SetObjectArrayElement(array, i, NativeAPI::createHookParameter(env, (jint) ((int)((bool)paramter)), HookJava::getJavaString(env, type)));
    }else if(type == "float"){
        env->SetObjectArrayElement(array, i, NativeAPI::createHookParameter(env, (jfloat) ((float&) paramter), HookJava::getJavaString(env, type)));
    }else if(type == "const char"){
        env->SetObjectArrayElement(array,i,NativeAPI::createHookParameter(env,HookJava::getJavaString(env,(const char*) paramter),HookJava::getJavaString(env,type)));
    }else if(type == "stl::string"){
        env->SetObjectArrayElement(array, i, NativeAPI::createHookParameter(env, HookJava::getJavaString(env, ((const stl::string*) paramter)->c_str()), HookJava::getJavaString(env, type)));
    }else{
        env->SetObjectArrayElement(array, i, NativeAPI::createHookParameter(env, (jlong) paramter, HookJava::getJavaString(env, type)));
    }
}

inline jobjectArray HookJava::getParameters(JNIEnv* env, std::vector<std::string> types, std::vector<jlong> ptrs, void* a, void* b, void* c, void* d, void* e, void* k, void* l, void* f, void* t, void* p){
    int size = types.size()+ptrs.size();
    jobjectArray array = (jobjectArray) env->NewGlobalRef(env->NewObjectArray(size, NativeAPI::PARAMETER, NULL));
    for(int i = 0;i < ptrs.size();i++)
        env->SetObjectArrayElement(array, i, NativeAPI::createHookParameter(env, ptrs[i], HookJava::getJavaString(env, "ptr")));
    for(int i = 0;i < types.size();i++){
        std::string type = types[i];
        if(i == 0)
            registerParameter(env, a, array, i+ptrs.size(), type);
        else if(i == 1)
            registerParameter(env, b, array, i+ptrs.size(), type);
        else if(i == 2)
            registerParameter(env, c, array, i+ptrs.size(), type);
        else if(i == 3)
            registerParameter(env, d, array, i+ptrs.size(), type);
        else if(i == 4)
            registerParameter(env, e, array, i+ptrs.size(), type);
        else if(i == 5)
            registerParameter(env, k, array, i+ptrs.size(), type);
        else if(i == 6)
            registerParameter(env, l, array, i+ptrs.size(), type);
        else if(i == 7)
            registerParameter(env, f, array, i+ptrs.size(), type);
        else if(i == 8)
            registerParameter(env, t, array, i+ptrs.size(), type);
        else if(i == 9)
            registerParameter(env, p, array, i+ptrs.size(), type);
    }
    return array;
}
#include <logger.h>
#include <horizon/types.h>

const ArgsBufferBuilder HookJava::getParameters(JNIEnv* env, void* self, std::vector<std::string> types, jobjectArray array){
    ArgsBufferBuilder builder;
    if(self != nullptr)
        builder.add<void*>(self);
    for (int i = 0;i < types.size();i++){
        jobject object = env->GetObjectArrayElement(array, i);
        std::string type = types[i];
        if(type == "int"){
            builder.add<int>(NativeAPI::getIntHookParameter(env, object));
        }else if(type == "bool"){
            builder.add<bool>(NativeAPI::getIntHookParameter(env, object) == 1);
        }else if(type == "stl::string"){
            builder.add<stl::string>(stl::string(NativeAPI::getStringHookParameter(env, object).c_str()));
        }else if(type == "float"){
            builder.add<float>(NativeAPI::getFloatHookParameter(env, object));
        }else if(type=="long"){
            builder.add<long long>(NativeAPI::getLongHookParameter(env,object));
        }else if(type=="char*"){
            builder.add<const char*>(NativeAPI::getStringHookParameter(env, object).c_str());
        }else{
            builder.add<void*>(NativeAPI::getPointerHookParameter(env, object));
        }
    }
    return builder;
}

template<typename T>
inline void registerHook(JNIEnv* env, Hook* hook, std::function<T(JNIEnv*,Hook*,Controller)> func, int v){
    HookManager::addCallback(
        SYMBOL(hook->lib.c_str(),hook->symbol.c_str()), 
        LAMBDA((HookManager::CallbackController* controller, void* self, void* a, void* b, void* c, void* d, void* e, void* k, void* l, void* f, void* t, void* p),{
            JNIEnv* env;
	        ATTACH_JAVA(env, JNI_VERSION_1_6){
                Controller ctr(controller);
                jobjectArray array = HookJava::getParameters(env, hook->args, {(jlong) &ctr, (jlong) self}, a, b, c, d, e, k, l, f, t, p);
                env->CallStaticVoidMethod(
                    HookJava::HOOK, HookJava::ID, 
                    HookJava::getJavaString(env, hook->callback), 
                    HookJava::getJavaString(env, hook->returnType), 
                    array
                );
                int size = (int) env->GetArrayLength(array);
                for(int i = 0;i < size;i++)
                    env->DeleteLocalRef(env->GetObjectArrayElement(array, i));
                env->DeleteGlobalRef(array);
                if(ctr.isResult()){
                    T result = func(env, hook, ctr);
                    ctr.end(env);
                    return result;
                }
            }
        },hook, func
    ), v);
}

void HookJava::init(){
    JNIEnv* env;
	ATTACH_JAVA(env, JNI_VERSION_1_6){
		HookJava::HOOK = reinterpret_cast<jclass>(env->NewGlobalRef(env->FindClass("com/core/api/module/Hook")));
        HookJava::DATA = reinterpret_cast<jclass>(env->NewGlobalRef(env->FindClass("com/core/api/module/JsonData")));
        HookJava::INIT = reinterpret_cast<jclass>(env->NewGlobalRef(env->FindClass("com/core/api/module/InitData")));
        HookJava::OBJECT = reinterpret_cast<jclass>(env->NewGlobalRef(env->FindClass("java/lang/Object")));
        HookJava::ID = env->GetStaticMethodID(HookJava::HOOK, "hookCallback", "(Ljava/lang/String;Ljava/lang/String;[Lcom/core/api/module/types/Parameter;)V");
        jclass Double = reinterpret_cast<jclass>(env->NewGlobalRef(env->FindClass("java/lang/Double")));
        HookJava::ID_INTAS = env->GetMethodID(Double, "intValue", "()I");
        HookJava::ID_FLOATAS = env->GetMethodID(Double, "floatValue", "()F");
        HookJava::ID_LongAS = env->GetMethodID(Double, "longValue", "()J");

        HookJava::obj = NativeAPI::createHookParameter(env, (jlong) 0, HookJava::getJavaString(env, "ptr"));

        std::vector<Init*> inits = HookJava::getInits(env);
        for(int i = 0;i < inits.size();i++)
            DLHandleManager::initializeHandle(inits[i]->lib.c_str(), inits[i]->name.c_str());

        std::vector<Hook*> hooks = HookJava::getHooks(env);
        for(int i = 0;i < hooks.size();i++){
            Hook* hook = hooks[i];
            HookJava::getJavaString(env, hook->callback); HookJava::getJavaString(env, hook->returnType);

            int v = HookManager::CALL | HookManager::LISTENER | HookManager::CONTROLLER;
            if(hook->priority == "post")
                v = HookManager::RETURN | HookManager::LISTENER | HookManager::CONTROLLER;

            if(hook->returnType == "void"){
                registerHook<void*>(env, hook, [](JNIEnv* env, Hook* hook, Controller ctr){
                    return (void*) HookJava::getPointerByObject(env, ctr.getResultHook());
                }, v);
            }else if(hook->returnType == "stl::string"){
                registerHook<stl::string>(env, hook, [](JNIEnv* env, Hook* hook, Controller ctr){
                    return stl::string(HookJava::getStringByObject(env, ctr.getResultHook()).c_str());
                }, v);
            }else if(hook->returnType == "int"){
                registerHook<int>(env, hook, [](JNIEnv* env, Hook* hook, Controller ctr){
                    return HookJava::getIntByObject(env, ctr.getResultHook());
                }, v);
            }else if(hook->returnType == "bool"){
                registerHook<bool>(env, hook, [](JNIEnv* env, Hook* hook, Controller ctr){
                    return HookJava::getBoolByObject(env, ctr.getResultHook());
                }, v);
            }else if(hook->returnType == "float"){
                registerHook<float>(env, hook, [](JNIEnv* env, Hook* hook, Controller ctr){
                    return HookJava::getFloatByObject(env, ctr.getResultHook());
                }, v);
            }
        }
	}
}

export(void,module_Hook_replace, jlong ptr) {
    ((Controller*) ptr)->replace();
}

export(void,module_Hook_setIsResult, jlong ptr, jboolean v) {
    ((Controller*) ptr)->setIsResult(v == JNI_TRUE);
}

export(void,module_Hook_setResult, jlong ptr, jobject v) {
    ((Controller*) ptr)->setResult(env->NewGlobalRef(v));
}