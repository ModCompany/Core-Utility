package com.core.api;

import com.core.api.engine.JniCallable;
import com.core.api.engine.JniInterface;
import com.zhekasmirnov.horizon.runtime.logger.Logger;

public class Injector {
    
    private long pointer;
    public Object[] args;

    public Injector(long ptr){
        this.pointer = init_injector(ptr);
    }

    public void call(String symbol){
        call(this.pointer, symbol);
    }

    public int getIntResult(String symbol){
        return getIntResult(this.pointer, symbol);
    }

    public float getFloatResult(String symbol){
        return getFloatResult(this.pointer, symbol);
    }

    public boolean getBoolResult(String symbol){
        return getBoolResult(this.pointer, symbol);
    }

    public String getStringResult(String symbol){
        return getStringResult(this.pointer, symbol);
    }

    public long getPointerResult(String symbol){
        return getPointerResult(this.pointer, symbol);
    }

    /*public void replace(String table,String symbol, Function func, String[] types){
        replace(this.pointer,table,symbol,func,types);
    }*/  

    public void push(Object[] a){
        args = a;
    }

    public void call(String symbol, Object...obj){
        callArgs(this.pointer, symbol, obj);
    }

    public void replace(String symbol,String table,String replace){
        replace(this.pointer, table, symbol, replace);
    }

    public void free(){
        free(this.pointer);
    }
    
    public static void tests(JniCallable c){

        test(c);
    }
    public native static long init_injector(long ptr);
    public native static int getIntResult(long ptr,String symbol);
    public native static float getFloatResult(long ptr,String symbol);
    public native static boolean getBoolResult(long ptr,String symbol);
    public native static long getPointerResult(long ptr, String symbol);
    public native static String getStringResult(long ptr,String symbol);
    public native static void call(long ptr,String symbol);
    public native static void replace(long ptr,String table,String symbol,String replace);
    //public native static void replace(long ptr, String table,String symbol, Function func, String[] args);
    public native static void callArgs(long ptr,String symbol, Object[] a);
    public static native void free(long ptr);
    public static native void test(JniCallable b);
}
