package com.core.api.mcpe.client;

public class GuiData {

    private long pointer;

    public GuiData(long pointer){
        this.pointer = pointer;
    }

    public void setTitle(String title){
        setTitle(this.pointer,title);
    }

    public void setSubtitle(String subtitle){
        setSubtitle(this.pointer,subtitle);
    }

    public void setActionMessage(String message){
        setActionMessage(this.pointer, message);
    }
    
    public static native void setTitle(long pointer,String title);
    public static native void setSubtitle(long pointer,String title);
    public static native void setActionMessage(long pointer,String title);
}
