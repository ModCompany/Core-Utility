#pragma once

#include <jni.h>
#include <string.h>



class JavaClass {
    public:
    JNIEnv* env;
    jobject object;
    
    JavaClass(JNIEnv*, jobject);
    int getInt(const char*);
    jobject runJsFunction(jobject, jobjectArray);
    float getFloat(const char*);
    const char* getString(const char*);
    bool getBool(const char*);
    std::string getClassName();
    static const char* release(JNIEnv* env,jstring);
    static std::string toString(JNIEnv* env,jstring);
};
