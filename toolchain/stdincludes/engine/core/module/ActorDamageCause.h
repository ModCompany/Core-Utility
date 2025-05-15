#pragma once
#include <jni.h>
#include <map>
#include <string>


enum ActorDamageCause {};

class ActorDamageSource {
    public:
        ActorDamageCause getCause() const;
};

class Actor;

std::__ndk1::pair<std::__ndk1::string, std::__ndk1::vector<std::__ndk1::string>> getDeadMessage(ActorDamageSource*, std::__ndk1::string, Actor*);

class RegisterDamageCause {  
    public:
        static std::map<int,jobject> types;
        static jclass JavaClass;
        static jmethodID DeadMessage;
        static void init();
        static void registerType(int,jobject);
};