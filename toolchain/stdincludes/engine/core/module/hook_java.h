#pragma once

#include <string>
#include <vector>
#include <java.h>
#include <map>

class Hook {
    public:
        std::string symbol, callback, priority, returnType;
        Hook(std::string symbol, std::string callback, std::string priority, std::string returnType): symbol(symbol), callback(callback), priority(priority), returnType(returnType){}
};

class ReturnType {
    public:
        virtual void* getConvertType(JNIEnv*, jobject){};
};

class HookJava {
    private:
        static std::map<std::string, ReturnType*> types;
        static std::map<std::string, jstring> cache;
    public:
        static jclass HOOK, DATA;
        static jmethodID ID;
        static jmethodID ID_INTAS;

        static std::vector<Hook*> getHooks(JNIEnv*);
        static void init();
        static jstring getJavaString(JNIEnv* env, std::string n){
            if(cache.find(n) != cache.end())
                return cache.find(n)->second;
            cache[n] = env->NewStringUTF(n.c_str());
            return cache.find(n)->second;
        }
        static void* getConvertType(JNIEnv*, std::string, jobject);
        static void regiserReturnType(std::string, ReturnType*);
};