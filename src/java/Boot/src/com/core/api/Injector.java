package com.core.api;

public class Injector {
    
    private long pointer;

    public Injector(long ptr){
        this.pointer = init_injector(ptr);
    }

    public int getIntResult(String symbol){
        return getIntResult(this.pointer, symbol);
    }

    public float getFloatResult(String symbol){
        return getFloatResult(this.pointer, symbol);
    }

    public void call(String symbol){
        call(this.pointer, symbol);
    }

    public native static long init_injector(long ptr);
    public native static int getIntResult(long ptr,String symbol);
    public native static float getFloatResult(long ptr,String symbol);
    public native static void call(long ptr,String symbol);
}
