package com.core.api;

import java.util.HashMap;

import com.core.api.engine.NativeVar;
import com.core.api.module.Hook;
import com.core.api.module.ModuleAPI;
import com.zhekasmirnov.innercore.api.mod.preloader.PreloaderAPI.Callback;

public class Boot {
    public static final String LOOGER_PREFIX = "CoreUtility";
    public static String dir;
    public static boolean cache_module = true;

    public static void log(String message){
        JsHelper.log(message);
    }

    public static void boot(HashMap<?, ?> data) {
        Callback.invokeCallback("CoreUtilityBoot", null, null, null, null, null, null, null, null, null, null);
        Hook.jsonLoad();
        ModuleAPI.init(dir);
        log("Java Loaded");
    }  

    public static void nativeFullLoaded(){
        /*log("Start test NativeVar");
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
        log("NativeVar result math: "+((long) native_var.get()));*/
    }

    public static native void nativeVarMath(long ptr);
}
 