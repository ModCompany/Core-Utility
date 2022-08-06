package com.core.api.mcpe.item;

import com.core.api.Injector;
import com.core.api.engine.PointerClass;
import com.core.api.module.types.Parameter;

public class Item extends PointerClass {
    public static native void registerItem(int id);
    public static native void overrideName(int id,int data, String name);
    public static native void overrideArmorValue(int id,float value);
    public static native void overrideColorHex(int id,int data,String hex);

    Injector injector;
    public Item(long ptr){
        super(ptr);
        injector = new Injector(ptr);
    }

    public void setIsMirroredArt(boolean value){
        injector.setArgsType(new String[] {"bool"}).call("_ZN4Item16setIsMirroredArtEb", new Object[] {
            Parameter.getBool(value)
        });
    }
}