package com.core.api;

import com.core.api.data.Tier;
import com.core.api.data.ItemTexture;
import com.zhekasmirnov.horizon.runtime.logger.Logger;
import org.mozilla.javascript.ScriptableObject;
import com.zhekasmirnov.innercore.api.mod.ScriptableObjectHelper;


public class Item {


    public static native void registerItem(int id);
    public static native void overrideName(int id, String name);
    public static native void overrideArmorValue(int id);

    public static void registerFood(){

    }






}