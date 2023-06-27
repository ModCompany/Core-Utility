package com.core.api.module;

public class HookManager {
    private native static void nativeSetEnabledHook(String callback, boolean enabled);
    private native static boolean nativeCanEnabledHook(String callback);
    
    public static void setEnabledHook(String callback, boolean enabled){
        nativeSetEnabledHook(callback, enabled);
    }

    public static boolean canEnabledHook(String callback){
        return nativeCanEnabledHook(callback);
    }
}
