package com.core.api.mcpe.client;

public class ClientInstance {
    private native static long getOptionsPointer(long pointer);
    private native static long getGuiPointer(long pointer);
    private native static void setCameraEntity(long pointer, long entity);
    long pointer;

    public ClientInstance(long pointer){
        this.pointer = pointer;
    }


    public void setCameraEntity(long entity){
        setCameraEntity(pointer,entity);
    }

    public long getPointer(){
        return pointer;
    }

    public Options getOptions(){
        return new Options(getOptionsPointer(pointer));
    }

    public GuiData getGuiData(){
        return new GuiData(getGuiPointer(pointer));
    }
}
