package com.core.api.mcpe.client;

import com.core.api.engine.PointerClass;

public class Options extends PointerClass{
    public static native void setRenderMobInfoState(boolean a);
    native private static int getUiProfilePointer(long pointer);

    public Options(long pointer){
        super(pointer);
    }
    public int getUiProfile(){
        return getUiProfilePointer(pointer);
    }
}
