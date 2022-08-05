#pragma once

#include <innercore_callbacks.h>

class NativeAPI {
    public:
        static jclass JNativeAPI, PARAMETER;
        static jmethodID constructorParameterLong, constructorParameterInt, constructorParameterFloat, constructorParameterString, getParameterLong, getParameterInt, getParameterFloat, getParameterString;
        static jobject createHookParameter(JNIEnv*, jlong, jstring);
        static jobject createHookParameter(JNIEnv*, jint, jstring);
        static jobject createHookParameter(JNIEnv*, jfloat, jstring);
        static jobject createHookParameter(JNIEnv*, jstring, jstring);

        static void* getPointerHookParameter(JNIEnv*, jobject);
        static int getIntHookParameter(JNIEnv*, jobject);
        static float getFloatHookParameter(JNIEnv*, jobject);
        static std::string getStringHookParameter(JNIEnv*, jobject);
        static long getLongHookParameter(JNIEnv*,jobject);
        static void init();
};