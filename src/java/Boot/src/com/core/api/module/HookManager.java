package com.core.api.module;

import java.util.HashMap;

import org.mozilla.javascript.Function;

import com.core.api.JsHelper;

public class HookManager {
    private native static void nativeSetEnabledHook(String callback, boolean enabled);
    private native static boolean nativeCanEnabledHook(String callback);
    private static HashMap<String, Function> listeners = new HashMap<>();
    
    public static void setEnabledHook(String callback, boolean enabled){
        nativeSetEnabledHook(callback, enabled);
    }

    public static boolean canEnabledHook(String callback){
        return nativeCanEnabledHook(callback);
    }

    public static void registerListener(String name, Function func){
        listeners.put(name, func);
    }

    public static void call(String name, Object[] args){
        JsHelper.callFunction(listeners.get(name), args);
    }
}