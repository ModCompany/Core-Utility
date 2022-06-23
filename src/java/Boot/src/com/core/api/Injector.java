package com.core.api;

import com.core.api.engine.PointerClass;

public class Injector {
    
    private long pointer;

    public Injector(long ptr){
        this.pointer = init_injector(ptr);
    }
    public Injector(PointerClass v){
        this.pointer = init_injector(v.getPointer());
    }

    public Injector setArgsType(String[] types){
        setArgsType(pointer, types);
        return this;
    }
    public Injector call(String symbol, Object[] args){
        call(this.pointer, symbol, args);
        return this;
    }

    public int getIntResult(String symbol, Object[] args){
        return getIntResult(this.pointer, symbol, args);
    }

    public float getFloatResult(String symbol, Object[] args){
        return getFloatResult(this.pointer, symbol, args);
    }

    public boolean getBoolResult(String symbol, Object[] args){
        return getBoolResult(this.pointer, symbol, args) == 1;
    }

    public String getStringResult(String symbol, Object[] args){
        return getStringResult(this.pointer, symbol, args);
    }

    public long getPointerResult(String symbol, Object[] args){
        return getPointerResult(this.pointer, symbol, args);
    }

    public void replace(String symbol,String table,String replace){
        replace(this.pointer, table, symbol, replace);
    }

    public void free(){
        free(this.pointer);
    }
    
    public native static long init_injector(long ptr);
    public native static long getOffset(long ptr);
    public native static long getOffset(long ptr,int offset);
    public native static int getIntResult(long ptr,String symbol, Object[] args);
    public native static float getFloatResult(long ptr,String symbol, Object[] args);
    public native static int getBoolResult(long ptr,String symbol, Object[] args);
    public native static long getPointerResult(long ptr, String symbol, Object[] args);
    public native static String getStringResult(long ptr,String symbol, Object[] args);
    public native static void call(long ptr,String symbol, Object[] args);

    public native static void replace(long ptr,String table,String symbol,String replace);
    public native static void setArgsType(long ptr, String[] types);
    public native static void callArgs(long ptr,String symbol, Object[] a);
    public static native void free(long ptr);
}
