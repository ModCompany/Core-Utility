package com.core.api.mcpe.client;

public class ClientInstance {
    native private static long getOptionsPointer(long pointer);
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
}
