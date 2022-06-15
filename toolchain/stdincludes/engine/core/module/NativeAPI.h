#pragma once

#include <innercore_callbacks.h>

class NativeAPI {
    public:
        static jclass JNativeAPI, PARAMETER;
        static jmethodID constructorParameterLong, constructorParameterInt, constructorParameterFloat, constructorParameterString;
        static jobject createHookParameter(JNIEnv*, jlong, jstring);
        static jobject createHookParameter(JNIEnv*, jint, jstring);
        static jobject createHookParameter(JNIEnv*, jfloat, jstring);
        static jobject createHookParameter(JNIEnv*, jstring, jstring);
        static void init();
};