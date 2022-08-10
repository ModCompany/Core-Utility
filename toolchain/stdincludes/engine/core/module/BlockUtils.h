#pragma once

#include <jni.h>

class BlockUtils {
    public:
        static jclass BlockUtilsJava;
        static jmethodID renderModelBlock;
        static void init();
};