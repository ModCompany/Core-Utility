package com.core.api.mcpe.api;

import com.core.api.engine.PointerClass;

public class Random extends PointerClass{
    native private static int nextIntPointer(long pointer, int max);
    public Random(long pointer){
        super(pointer);
    }
    public int nextInt(int max){
        return nextIntPointer(pointer, max);
    }
}
