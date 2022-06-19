package com.core.api.mcpe.client;

import com.core.api.engine.PointerClass;

public class ClientInstance extends PointerClass {
    private native static long getOptionsPointer(long pointer);
    private native static long getGuiPointer(long pointer);
    private native static void setCameraEntity(long pointer, long entity);

    public ClientInstance(long pointer){
        super(pointer);
    }

    public void setCameraEntity(long entity){
        setCameraEntity(pointer,entity);
    }
    public Options getOptions(){
        return new Options(getOptionsPointer(pointer));
    }

    public GuiData getGuiData(){
        return new GuiData(getGuiPointer(pointer));
    }
}
