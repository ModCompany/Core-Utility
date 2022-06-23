package com.core.api.mcpe.block.api;

import com.core.api.engine.PointerClass;

public class ItemState extends PointerClass {
    native public static long newClass(int hz, String name, int hz1);
    public ItemState(int hz, String name, int hz1){
        super(newClass(hz, name, hz1));
    }
}
