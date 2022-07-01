#pragma once

struct NativeSaver {
    static jclass NativeSaverClass;
    static jmethodID readID, saveID;
    static void init();
};