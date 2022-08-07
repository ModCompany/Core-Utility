#pragma once

#include <string>
#include <jni.h>
#include <map>

class NativeType {
    public:
        virtual jobject getJava(char*) const = 0;
        virtual char* getCpp(jobject) const = 0;
};

class NativeVar {
    private:
        std::string type;
        jobject value;
        static std::map<std::string, NativeType*> types;
    public:
        bool isFinalize;
        static void init();
        static void registerType(std::string, NativeType*);
        NativeVar();
        NativeVar(std::string);
        NativeVar(JNIEnv*, jobject, std::string);
        NativeVar(JNIEnv*, char*, std::string);
        ~NativeVar();

        void setType(std::string);

        jobject get(JNIEnv*) const;
        void set(JNIEnv*,jobject);
        char* getCpp(JNIEnv*) const;
        void setCpp(JNIEnv*,char*);
        void setFinalize(bool);
};