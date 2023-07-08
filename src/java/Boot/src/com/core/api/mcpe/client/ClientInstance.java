package com.core.api.mcpe.client;

import com.core.api.engine.PointerClass;

public class ClientInstance extends PointerClass {
    private native static long getOptionsPointer(long pointer);
    private native static long getGuiPointer(long pointer);
    private native static void setCameraEntity(long pointer, long entity);
    private native static void renderDestroyBlock(long pointer,int x,int y,int z,float speed);
    public ClientInstance(long pointer){
        super(pointer);
    }

    public void setCameraEntity(long entity){
        setCameraEntity(pointer,entity);
    }

    public void renderDestroyBlock(int x,int y,int z,double speed){
        renderDestroyBlock(pointer, x, y, z,(float) speed);
    }

    public void renderDestroyBlock(int x,int y,int z,float speed){
        renderDestroyBlock(pointer, x, y, z, speed);
    }

    public Options getOptions(){
        return new Options(getOptionsPointer(pointer));
    }

    public GuiData getGuiData(){
        return new GuiData(getGuiPointer(pointer));
    }
}
