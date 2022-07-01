package com.core.api.mcpe.item;

public class Item {
    public static native void registerItem(int id);
    public static native void overrideName(int id,int data, String name);
    public static native void overrideArmorValue(int id,float value);
    
}