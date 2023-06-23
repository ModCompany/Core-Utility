#include <core/module/HookAPI.hpp>
#include <core/module/NativeAPI.h>
#include <core/module/NativeVar.hpp>
#include <functional>
#include <hook.h>
#include <symbol.h>
#include <cstdarg>

template<int N>
struct alignas(void*) Buff { unsigned char data[N]; };

struct ArgsReader {
    const unsigned char *data;
    int pos = 0;

    explicit ArgsReader(const unsigned char *data) : data(data) {}

    template<typename T>
    const T& read() {
        int p = ((pos + alignof(T) - 1) / alignof(T)) * alignof(T);
        pos = p + sizeof(T);
        return *reinterpret_cast<const T*>(data + p);
    }
};

std::vector<HookRegistry*> HookRegistry::hooks;
jclass HookAPI::HookAPIClass;
jmethodID HookAPI::hookId;

HookRegistry::HookRegistry(std::string lib, std::string symbol, std::string callback, std::string priority, std::string return_type, std::vector<std::string> args_types): 
    symbol(symbol), callback(callback), priority(priority), lib(lib), return_type(return_type), args_types(args_types){

}

void HookRegistry::addHook(std::string lib, std::string symbol, std::string callback, std::string priority, std::string return_type, std::vector<std::string> args_types){
    HookRegistry::hooks.push_back(new HookRegistry(lib, symbol, callback, priority, return_type, args_types));
}

#define newNativeVar(T, env, value, type) env->NewGlobalRef(env->NewObject(NativeVar::NativeVarClass, NativeVar::NativeVarConstructor, (jlong) new NativeVar(env, (new TypeBuilder())->set<T>(value), type)))
#define setArgToJava(T, env, i, array, args, type) env->SetObjectArrayElement(array, i, newNativeVar(T, env, args.read<T>(), type));
// template<typename T>
// void setArgToJava(JNIEnv* env, int i, jobjectArray array, ArgsReader args, std::string type){
//     env->SetObjectArrayElement(array, i, newNativeVar(void*, env, args.read<T>(), type));
// }

inline jobjectArray getParameters(JNIEnv* env, std::vector<std::string> types, ArgsReader args){
    jobjectArray array = (jobjectArray) env->NewGlobalRef(env->NewObjectArray(types.size(), NativeVar::NativeVarClass, NULL));

    int i = 0;
    for(auto it = types.begin();it != types.end();it++){
        std::string type = *it;
        if(type == "ptr")
            setArgToJava(void*, env, i, array, args, "ptr");
        i++;
        
    }

    return array;
}

template<typename T>
inline void registerHook(JNIEnv* env, HookRegistry* hook, std::function<T(JNIEnv*,HookRegistry*)> func, int v){
    HookManager::addCallback(
        SYMBOL(hook->lib.c_str(), hook->symbol.c_str()), 
        LAMBDA((HookManager::CallbackController* controller, void* self, const unsigned char* data),{
            JNIEnv* env;
	        ATTACH_JAVA(env, JNI_VERSION_1_6){
                std::vector<std::string> types = hook->args_types;
  
                jobjectArray array = getParameters(env, types, ArgsReader(data));

                env->CallStaticVoidMethod(
                    HookAPI::HookAPIClass, HookAPI::hookId,  
                    array
                );
                env->DeleteGlobalRef(array);
                /*Controller ctr(controller);
                jobjectArray array = HookJava::getParameters(env, hook->args, {(jlong) &ctr, (jlong) self}, a, b, c, d, e, k, l, f, t, p);
                env->CallStaticVoidMethod(
                    HookJava::HOOK, HookJava::ID, 
                    HookJava::getJavaString(env, hook->callback), 
                    HookJava::getJavaString(env, hook->returnType), 
                    array
                );
                env->DeleteGlobalRef(array);
                if(ctr.isResult()){
                    T result = func(env, hook, ctr);
                    ctr.end(env);
                    return result;
                }*/
            }
        },hook, func
    ), v);
}

void HookRegistry::hooksLoaded(JNIEnv* env){
    auto it = HookRegistry::hooks.begin();
    while(it != HookRegistry::hooks.end()){
        registerHook<void*>(env, *it, [](JNIEnv* env, HookRegistry* hook){
            return nullptr;
        }, HookManager::RETURN | HookManager::LISTENER | HookManager::CONTROLLER);

        it++;
    }
}

void HookAPI::init(){
    HookRegistry::addHook(
        "mcpe",
        "_ZN5Actor6attackERS_", 
        "ToolTip",
        "pre",
        "void",
        {"ptr"}
    );
    JNIEnv* env;
	ATTACH_JAVA(env, JNI_VERSION_1_6){
        HookAPI::HookAPIClass = reinterpret_cast<jclass>(env->NewGlobalRef(env->FindClass("com/core/api/module/HookAPI")));
        HookAPI::hookId = env->GetStaticMethodID(HookAPI::HookAPIClass, "hook", "([Lcom/core/api/engine/NativeVar;)V");

        HookRegistry::hooksLoaded(env);
    }
}