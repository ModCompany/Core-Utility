package com.core.api.mcpe.block;

import com.core.api.engine.PointerClass;

public class BlockLegacy extends PointerClass {
    native public void addState(long pointer, String name, int min, int max, int v);
    public BlockLegacy(long ptr){
        super(ptr);
    }

    public void addState(String name, int min, int max){
        addState(pointer, name, min, max, 0);
    }
    public void addState(String name, int min, int max, int v){
        addState(pointer, name, min, max, v);
    }
}
