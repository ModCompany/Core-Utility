package com.core.api.engine;

public class DataOffset {
 
    private long pointer;

    public DataOffset(long pointer){
        this.pointer = pointer;
    }

    public boolean getBool(){
        return getBool(pointer);
    }

    public boolean getBool(int offset){
        return getBoolOffset(pointer,offset);
    }

    public int getInt(){
        return getInt(pointer);
    }

    public int getInt(int offset){
        return getIntOffset(pointer,offset);
    }

    public long getPointer(){
        return getPointer(pointer);
    }

    public long getPointer(int offset){
        return getPointerOffset(pointer, offset);
    }

    public String getString(){
        return getString(pointer);
    }

    public String getString(int offset){
        return getStringOffset(pointer, offset);
    }
    
    public void setOffset(int offset){
        setOffset(pointer,offset);
    }

    public long get(){
        return this.pointer;
    }

    public static native void setOffset(long ptr,int offset);
    public static native long getPointer(long ptr);
    public static native long getPointerOffset(long ptr,int offset);
    public static native int getInt(long ptr);
    public static native int getIntOffset(long ptr,int offset);
    public static native boolean getBool(long ptr);
    public static native boolean getBoolOffset(long ptr,int offset);
    public static native String getString(long ptr);
    public static native String getStringOffset(long ptr,int offset);
}
