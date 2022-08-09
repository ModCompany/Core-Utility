package com.core.api.mcpe.entity;

import com.core.api.engine.PointerClass;

public class LocalPlayer extends Player {
    public LocalPlayer(long pointer){
        super(pointer);
    }
    public LocalPlayer(PointerClass pointer){
        super(pointer);
    }
}
