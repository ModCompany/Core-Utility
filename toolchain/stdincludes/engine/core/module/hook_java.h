#pragma once

#include <string>
#include <vector>
#include <java.h>
#include <map>
#include <core/JavaClass.h>

class Hook {
    public:
        std::string symbol, callback, priority, returnType;
        Hook(std::string symbol, std::string callback, std::string priority, std::string returnType): symbol(symbol), callback(callback), priority(priority), returnType(returnType){}
};

class HookJava {
    private:
        static std::map<std::string, jstring> cache;
    public:
        static jclass HOOK, DATA;
        static jmethodID ID;
        static jmethodID ID_INTAS;

        static int getIntByObject(JNIEnv* env, jobject v){
            return (int) (env->CallIntMethod(v, HookJava::ID_INTAS));
        }

        static bool getBoolByObject(JNIEnv* env, jobject v){
            return getIntByObject(env, v) == 1;
        }

        static std::string getStringByObject(JNIEnv* env, jobject v){
            Logger::debug("TEST", "getStringByObject");
            std::string str = JavaClass::toString(env, (jstring) v);
            Logger::debug("TEST", str.c_str());
            return str;
        }

        static std::vector<Hook*> getHooks(JNIEnv*);
        static void init();
        static jstring getJavaString(JNIEnv* env, std::string n){
            Logger::debug("TEST", n.c_str());
            if(cache.find(n) != cache.end())
                return cache.find(n)->second;
            cache[n] = env->NewStringUTF(n.c_str());
            return cache.find(n)->second;
        }
};