package com.core.api.mcpe.client;

import com.core.api.engine.PointerClass;

public class GuiData extends PointerClass {

    public GuiData(long pointer){
        super(pointer);
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

    public float getGuiScale(){
        return getGuiScale(pointer);
    }

    public void setGuiScale(float value){
        setGuiScale(pointer, value);
    }

    public float getWindowWidth(){
        return getWindowWidth(pointer);
    }

    public float getWindowHeigth(){
        return getWindowHeigth(pointer);
    }

    public float getDisplayHeigth(){
        return getDisplayHeigth(pointer);
    }

    public float getDisplayWidth(){
        return getDisplayWidth(pointer);
    }

    public static native float getGuiScale(long pointer);
    public static native void setGuiScale(long pointer, float value);
    public static native float getWindowWidth(long pointer);
    public static native float getWindowHeigth(long pointer);
    public static native float getDisplayWidth(long pointer);
    public static native float getDisplayHeigth(long pointer);
    public static native void setTitle(long pointer,String title);
    public static native void setSubtitle(long pointer,String title);
    public static native void setActionMessage(long pointer,String title);
}
