#pragma once

#include <string>
#include <vector>
#include <java.h>
#include <map>
#include <core/JavaClass.h>
#include <core/VtableHelper.h>
#include <unordered_map>
#include <thread>
#include <innercore_callbacks.h>

class Hook {
    public:
        std::string symbol, callback, priority, returnType, lib;
        std::vector<std::string> args;
        bool legacyListener;
        int version;
        Hook(std::string symbol, std::string callback, std::string priority, std::string returnType, std::vector<std::string> args, std::string lib, bool legacyListener, int version): symbol(symbol), callback(callback), priority(priority), returnType(returnType), args(args), lib(lib), legacyListener(legacyListener), version(version){}
};

class Init {
    public:
        std::string name, lib;
        Init(std::string name, std::string lib): name(name), lib(lib){}
};

class CUHookManager {
    private:
        static std::unordered_map<std::string, bool> enabled;
    public:
        static void setEnabledHook(std::string name, bool value);
        static bool canEnabledHook(std::string name);
};

class HookJava {
    private:
        static std::unordered_map<std::string, jstring> cache;
    public:
        static std::unordered_map<std::thread::id, JNIEnv*> env_map;
        static jclass HOOK, DATA, OBJECT, INIT;
        static jmethodID ID, ID_NEW;
        static jmethodID ID_INTAS;
        static jmethodID ID_FLOATAS;
        static jmethodID ID_LongAS;
        static jobject obj;

        static int getIntByObject(JNIEnv* env, jobject v){
            return (int) (env->CallIntMethod(v, HookJava::ID_INTAS));
        }

        static jlong getPointerByObject(JNIEnv* env, jobject v){
            return (env->CallLongMethod(v, HookJava::ID_LongAS));
        }

        static bool getBoolByObject(JNIEnv* env, jobject v){
            return getIntByObject(env, v) == 1;
        }

        static float getFloatByObject(JNIEnv* env, jobject v){
            return (float) (env->CallFloatMethod(v, HookJava::ID_FLOATAS));
        }

        inline static jobjectArray getParameters(JNIEnv*, std::vector<std::string>, std::vector<jlong>, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*);
        static const ArgsBufferBuilder getParameters(JNIEnv*, void*, std::vector<std::string>, jobjectArray);
        inline static JNIEnv* get_jni_env() {
            std::thread::id thread_id = std::this_thread::get_id();
            auto it = env_map.find(thread_id);
            if (it != env_map.end()) {
                return it->second;
            } else {
                JavaVM* jvm = JavaCallbacks::getJavaVM();
                JNIEnv* env;
                //jint res = jvm->AttachCurrentThread(&env, NULL);
                jvm->GetEnv((void**) &env, JNI_VERSION_1_6);
                env_map[thread_id] = env;
                return env;
            }
        }
        
        static std::string getStringByObject(JNIEnv* env, jobject v){
            jstring t = (jstring) v;
            std::string str = JavaClass::toString(env, t);
            return str;
        }

        static std::vector<Hook*> getHooks(JNIEnv*);
        static std::vector<Init*> getInits(JNIEnv*);
        static void init();
        static jstring getJavaString(JNIEnv* env, std::string n){
            auto it = cache.find(n);
            if(it != cache.end())
                return it->second;
            jstring value = (jstring) env->NewGlobalRef(env->NewStringUTF(n.c_str()));
            cache[n] = value;
            return value;
        }
};