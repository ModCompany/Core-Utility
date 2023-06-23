package com.core.api;

import java.util.HashMap;

import com.core.api.engine.NativeVar;
import com.core.api.module.Hook;
import com.zhekasmirnov.horizon.runtime.logger.Logger;

class Boot {
    public static final String LOOGER_PREFIX = "CoreUtility";

    public static void log(String message){
        Logger.debug(message);
    }

    public static void boot(HashMap<?, ?> data) {
        Hook.jsonLoad();
        log("Java Loaded");
    }  

    public static void nativeFullLoaded(){
        log("Start test NativeVar");
        NativeVar native_var = new NativeVar(1000l, "ptr");
        log("NativeVar test, status: 1");
        long value = (long) native_var.get();
        log("NativeVar test, status: 1.5");
        native_var.set(value / 2);
        log("NativeVar test, status: 2");
        native_var.set(((long) native_var.get()) + 5);
        log("NativeVar test, status: 3");
        nativeVarMath(native_var.getPointer());
        log("print result math NativeVar...");
        log("NativeVar result math: "+((long) native_var.get()));
    }

    public static native void nativeVarMath(long ptr);
}
 