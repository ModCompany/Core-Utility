package com.core.api.mcpe.client;

import com.core.api.engine.PointerClass;
import com.core.api.innnercore.GlobalContext;
import com.core.api.mcpe.api.Vec2;

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

    public Vec2 toWindow(float x, float y){
        float display_x = getDisplayWidth();
        float display_y = getDisplayWidth();
        float window_x = getWindowWidth();
        float window_y = getWindowHeigth();
        return new Vec2(x/display_x*window_x, y/display_y*window_y);
    }

    public Vec2 toDisplay(float x, float y){
        float display_x = getDisplayWidth();
        float display_y = getDisplayWidth();
        float window_x = getWindowWidth();
        float window_y = getWindowHeigth();
        return new Vec2(x/window_x*display_x, y/window_y*display_y);
    }

    public static Vec2 toWindowStatic(float x, float y){
        return GlobalContext.getClientInstance().getGuiData().toWindow(x, y);
    }

    public static Vec2 toDisplayStatic(float x, float y){
        return GlobalContext.getClientInstance().getGuiData().toDisplay(x, y);
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
