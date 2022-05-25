package com.core.api.mcpe.entity;

public class ServerPlayer {
    long pointer;
    public ServerPlayer(long pointer){
        this.pointer = pointer;
    }

    public long getPointer(){
        return pointer;
    }
}
