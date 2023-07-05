package com.core.api;

import com.core.api.engine.CppClass;
import com.core.api.engine.DataOffset;
import com.core.api.engine.NativeVar;
import com.core.api.engine.PointerClass;
import com.core.api.module.types.Parameter;

public class Injector {
    
    private long pointer;

    public Injector(long ptr){
        this.pointer = init_injector(ptr);
    }
    public Injector(Long ptr){
        this.pointer = init_injector(ptr);
    }
    public Injector(NativeVar native_var){
        this((long) native_var.get());
    }
    public Injector(PointerClass v){
        this.pointer = init_injector(v.getPointer());
    }
    public Injector(String lib, String symbol, String types){
        this(0);
    }
    
    public Injector setArgsType(String[] types){
        setArgsType(pointer, types);
        return this;
    }
    public Injector setArgsTypes(String...types){
       return setArgsType(types);
    }
    public Injector setArgsTypes(){
        return setArgsType(new String[] {});
    }

    private String table = "";


    public Injector call(String symbol, Object[] args, String table){
        call(this.pointer, symbol, args, table != "", table);
        return this;
    }

    public Injector call(String symbol){
        return call(symbol, new Object[] {}, table);
    }
    public Injector call(String symbol, Object[] args){
        return call(symbol, args, table);
    }

    public Injector apply(String symbol, Parameter... args){
        return call(symbol, args);
    }

    public Injector setTable(String table){
        this.table = table;
        return this;
    }

    public int getIntResult(String symbol, Object[] args, String table){
        return getIntResult(this.pointer, symbol, args, table != "", table);
    }
    public int getIntResult(String symbol){
        return getIntResult(symbol, new Object[] {}, table);
    }
    public int getIntResult(String symbol, Object[] args){
        return getIntResult(symbol, args, table);
    }

    public float getFloatResult(String symbol, Object[] args, String table){
        return getFloatResult(this.pointer, symbol, args, table != "", table);
    }
    public float getFloatResult(String symbol){
        return getFloatResult(symbol, new Object[] {}, table);
    }
    public float getFloatResult(String symbol, Object[] args){
        return getFloatResult(symbol, args, table);
    }

    public boolean getBoolResult(String symbol, Object[] args, String table){
        return getBoolResult(this.pointer, symbol, args, table != "", table) == 1;
    }
    public boolean getBoolResult(String symbol){
        return getBoolResult(symbol, new Object[] {}, table);
    }
    public boolean getBoolResult(String symbol, Object[] args){
        return getBoolResult(symbol, args, table);
    }

    public String getStringResult(String symbol, Object[] args, String table){
        return getStringResult(this.pointer, symbol, args, table != "", table);
    }
    public String getStringResult(String symbol){
        return getStringResult(symbol, new Object[] {}, table);
    }
    public String getStringResult(String symbol, Object[] args){
        return getStringResult(symbol, args, table);
    }

    public long getPointerResult(String symbol, Object[] args, String table){
        return getPointerResult(this.pointer, symbol, args, table != "", table);
    }
    public long getPointerResult(String symbol){
        return getPointerResult(symbol, new Object[] {}, table);
    }
    public long getPointerResult(String symbol, Object[] args){
        return getPointerResult(symbol, args, table);
    }

    public Injector replace(String table,String symbol,String replace){
        replace(this.pointer, table, symbol, replace);
        return this;
    }

    public Injector setDebug(boolean value){
        setDebug(this.pointer, value);
        return this;
    }
    boolean isFree = false;
    public void free(){
        if(!isFree)
            free(this.pointer);
        isFree = true;
    }

    @Override
    public void finalize() throws Throwable {
        free();
    }

    public DataOffset getData(){
        return new DataOffset(getOffset(pointer));
    }
    public DataOffset getData(int offset){
        return new DataOffset(getOffset(pointer, offset));
    }

    public Injector setLib(String name){
        setLib(pointer, name);
        return this;
    }

    public static CppClass newObject(String symbol, String[] types, Object[] args){
        return new CppClass(nativeNewObject(symbol, types, args));
    }

    public static CppClass newObject(String lib, String symbol, String[] types, Object[] args){
        return new CppClass(nativeNewObjectAndLib(lib, symbol, types, args));
    }
    
    public native static long nativeNewObject(String symbol, String[] types, Object[] args);
    public native static long nativeNewObjectAndLib(String lib, String symbol, String[] types, Object[] args);
    public native static long init_injector(long ptr);
    //public native static long constructor(String symbol, String lib, String[] types, Object[] args);
    public native static void setDebug(long ptr,boolean value);
    public native static long getOffset(long ptr);
    public native static long getOffset(long ptr,int offset);

    public native static int getIntResult(long ptr,String symbol, Object[] args, boolean virt, String table);
    public native static float getFloatResult(long ptr,String symbol, Object[] args, boolean virt, String table);
    public native static int getBoolResult(long ptr,String symbol, Object[] args, boolean virt, String table);
    public native static long getPointerResult(long ptr, String symbol, Object[] args, boolean virt, String table);
    public native static String getStringResult(long ptr,String symbol, Object[] args, boolean virt, String table);

    public native static void call(long ptr,String symbol, Object[] args, boolean virt, String table);
    public native static void replace(long ptr,String table,String symbol,String replace);
    public native static void setArgsType(long ptr, String[] types);
    public native static void setLib(long ptr, String name);
    public static native void free(long ptr);


}
