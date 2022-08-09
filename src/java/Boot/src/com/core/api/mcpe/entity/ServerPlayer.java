package com.core.api.mcpe.entity;

import com.core.api.engine.PointerClass;

public class ServerPlayer extends Player {
    public ServerPlayer(long pointer){
        super(pointer);
    }
    public ServerPlayer(PointerClass pointer){
        super(pointer);
    }
}
