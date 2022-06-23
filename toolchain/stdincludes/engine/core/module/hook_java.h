#pragma once

#include <string>
#include <vector>
#include <java.h>
#include <map>
#include <core/JavaClass.h>
#include <core/VtableHelper.h>

class Hook {
    public:
        std::string symbol, callback, priority, returnType;
        std::vector<std::string> args;
        Hook(std::string symbol, std::string callback, std::string priority, std::string returnType, std::vector<std::string> args): symbol(symbol), callback(callback), priority(priority), returnType(returnType), args(args){}
};

class HookJava {
    private:
        static std::map<std::string, jstring> cache;
    public:
        static jclass HOOK, DATA, OBJECT;
        static jmethodID ID;
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
        static const ArgsBufferBuilder getParameters(JNIEnv*, std::vector<std::string>, jobjectArray);
        
        static std::string getStringByObject(JNIEnv* env, jobject v){
            jstring t = (jstring) v;
            std::string str = JavaClass::toString(env, t);
            return str;
        }

        static std::vector<Hook*> getHooks(JNIEnv*);
        static void init();
        static jstring& getJavaString(JNIEnv* env, std::string n){
            if(cache.find(n) != cache.end())
                return cache.find(n)->second;
            cache[n] = (jstring) env->NewGlobalRef(env->NewStringUTF(n.c_str()));
            return cache.find(n)->second;
        }
};