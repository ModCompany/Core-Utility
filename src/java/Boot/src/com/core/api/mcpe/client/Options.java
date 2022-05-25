package com.core.api.mcpe.client;

public class Options {
    public static native void setRenderMobInfoState(boolean a);
    native private static int getUiProfilePointer(long pointer);

    long pointer;
    public Options(long pointer){
        this.pointer = pointer;
    }
    public int getUiProfile(){
        return getUiProfilePointer(pointer);
    }
}
