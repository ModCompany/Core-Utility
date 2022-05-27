package com.core.api;

public class Injector {
    

    public native static long init_injector(long ptr);
    public native static void getIntResult(long ptr,String table,String symbol);
    public native static void getFloatResult(long ptr,String table,String symbol);
    public native static void call(long ptr,String table,String symbol);
}
