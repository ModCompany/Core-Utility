#pragma once

#include <vector>
#include <string>
#include <jni.h>
#include <java.h>

class HookRegistry {
    public:
        std::string symbol, callback, priority, lib, return_type;
        std::vector<std::string> args_types;
        static std::vector<HookRegistry*> hooks;
        HookRegistry(std::string, std::string, std::string, std::string, std::string, std::vector<std::string>);

        static void addHook(std::string, std::string, std::string, std::string, std::string, std::vector<std::string>);
        static void hooksLoaded(JNIEnv* env);
};

class HookAPI {
    public:
        static jclass HookAPIClass;
        static jmethodID hookId;
        static void init();
};