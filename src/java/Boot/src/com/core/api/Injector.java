package com.core.api;

import com.core.api.engine.DataOffset;
import com.core.api.engine.PointerClass;

public class Injector {
    
    private long pointer;

    public Injector(long ptr){
        this.pointer = init_injector(ptr);
    }
    public Injector(PointerClass v){
        this.pointer = init_injector(v.getPointer());
    }
    public Injector(){
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
    public Injector call(String symbol, Object[] args, String table){
        call(this.pointer, symbol, args, table != "", table);
        return this;
    }
    public Injector call(String symbol){
        return call(symbol, new Object[] {}, "");
    }
    public Injector call(String symbol, Object[] args){
        return call(symbol, args, "");
    }

    public int getIntResult(String symbol, Object[] args, String table){
        return getIntResult(this.pointer, symbol, args, table != "", table);
    }
    public int getIntResult(String symbol){
        return getIntResult(symbol, new Object[] {}, "");
    }
    public int getIntResult(String symbol, Object[] args){
        return getIntResult(symbol, args, "");
    }

    public float getFloatResult(String symbol, Object[] args, String table){
        return getFloatResult(this.pointer, symbol, args, table != "", table);
    }
    public float getFloatResult(String symbol){
        return getFloatResult(symbol, new Object[] {}, "");
    }
    public float getFloatResult(String symbol, Object[] args){
        return getFloatResult(symbol, args, "");
    }

    public boolean getBoolResult(String symbol, Object[] args, String table){
        return getBoolResult(this.pointer, symbol, args, table != "", table) == 1;
    }
    public boolean getBoolResult(String symbol){
        return getBoolResult(symbol, new Object[] {}, "");
    }
    public boolean getBoolResult(String symbol, Object[] args){
        return getBoolResult(symbol, args, "");
    }

    public String getStringResult(String symbol, Object[] args, String table){
        return getStringResult(this.pointer, symbol, args, table != "", table);
    }
    public String getStringResult(String symbol){
        return getStringResult(symbol, new Object[] {}, "");
    }
    public String getStringResult(String symbol, Object[] args){
        return getStringResult(symbol, args, "");
    }

    public long getPointerResult(String symbol, Object[] args, String table){
        return getPointerResult(this.pointer, symbol, args, table != "", table);
    }
    public long getPointerResult(String symbol){
        return getPointerResult(symbol, new Object[] {}, "");
    }
    public long getPointerResult(String symbol, Object[] args){
        return getPointerResult(symbol, args, "");
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
    public void finalize() {
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
    
    public native static long init_injector(long ptr);
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
