#pragma once

#include <string>
#include <vector>
#include <java.h>

class Hook {
    public:
        std::string symbol, callback;
        Hook(std::string symbol, std::string callback): symbol(symbol), callback(callback){}
};

class HookJava {
    public:
        static jclass HOOK, DATA;
        static jmethodID ID;
        static std::vector<Hook*> getHooks(JNIEnv*);
        static void init();
};