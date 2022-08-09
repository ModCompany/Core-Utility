package com.core.api.mcpe.entity;

import com.core.api.engine.PointerClass;

public class Mob extends Actor {
    public Mob(long ptr) {
        super(ptr);
    }
    public Mob(PointerClass ptr){
        this(ptr.getPointer());
    }
}
