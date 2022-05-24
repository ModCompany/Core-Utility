package com.core.api;

import com.zhekasmirnov.innercore.api.mod.adaptedscript.AdaptedScriptAPI.Item;
import com.zhekasmirnov.innercore.api.runtime.Callback;

public class NativeCallback {

    public static void onEnchant(int id){
        Callback.invokeCallback("OnEnchant",id);

    }
}