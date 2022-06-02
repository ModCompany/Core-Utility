package com.core.api.mcpe.client;

public class ClientInstance {
    private native static long getOptionsPointer(long pointer);
    private native static long getGuiPointer();
    long pointer;

    public ClientInstance(long pointer){
        this.pointer = pointer;
    }

    public long getPointer(){
        return pointer;
    }

    public Options getOptions(){
        return new Options(getOptionsPointer(pointer));
    }

    public GuiData getGuiData(){
        return new GuiData(getGuiPointer());
    }
}
