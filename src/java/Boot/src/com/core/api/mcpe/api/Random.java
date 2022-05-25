package com.core.api.mcpe.api;

public class Random {
    native private static int nextIntPointer(long pointer, int max);
    long pointer;
    public Random(long pointer){
        this.pointer = pointer;
    }
    public int nextInt(int max){
        return nextIntPointer(pointer, max);
    }
}
