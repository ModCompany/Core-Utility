#pragma once

#include <jni.h>
#include <string.h>



class JavaClass {
    public:
    JNIEnv* env;
    jobject object;
    
    JavaClass(JNIEnv*, jobject);
    int getInt(const char*);
    float getFloat(const char*);
    const char* getString(const char*);
    bool getBool(const char*);
    
    static const char* release(JNIEnv* env,jstring);
};

class JniConverter {
    public:
    class JavaObject {
        public:

    };

    class JavaClass {
        public:
    };
};

class JavaHelper {
    public:

    static const char* release(jstring);
};