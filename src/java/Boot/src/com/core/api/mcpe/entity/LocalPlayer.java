package com.core.api.mcpe.entity;

public class LocalPlayer {
    long pointer;
    public LocalPlayer(long pointer){
        this.pointer = pointer;
    }

    public long getPointer(){
        return this.pointer;
    }
}
