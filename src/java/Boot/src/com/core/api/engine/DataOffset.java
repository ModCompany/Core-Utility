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

    public float getFloat(){
        return getFloat(pointer);
    }

    public float getFloat(int offset){
        return getFloatOffset(pointer,offset);
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

    public void setBool(boolean value){
        setBool(pointer,value);
    }

    public void setBool(int offset,boolean value){
        setBoolOffset(pointer,offset,value);
    }

    public void setInt(int value){
        setInt(pointer,value);
    }

    public void setInt(int offset,int value){
        setIntOffset(pointer, offset, value);
    }

    public void setFloat(float value){
        setFloat(pointer,value);
    }

    public void setFloat(int offset,int value){
        setFloatOffset(pointer, offset, value);
    }

    public void setPointer(long value){
        setPointer(pointer,value);
    }

    public void setPointer(int offset,long value){
        setFloatOffset(pointer, offset, value);
    }

    public void setString(String value){
        setString(pointer,value);
    }

    public void setString(int offset,String value){
        setStringOffset(pointer,offset,value);
    }

    public long get(){
        return this.pointer;
    }

    public void free(){
        free(this.pointer);
    }

    @Override
    protected void finalize() throws Throwable {
        free(pointer);
    }
    
    public static native void free(long ptr);
    public static native void setOffset(long ptr,int offset);
    public static native long getPointer(long ptr);
    public static native long getPointerOffset(long ptr,int offset);
    public static native int getInt(long ptr);
    public static native int getIntOffset(long ptr,int offset);
    public static native float getFloat(long ptr);
    public static native float getFloatOffset(long ptr,int offset);
    public static native boolean getBool(long ptr);
    public static native boolean getBoolOffset(long ptr,int offset);
    public static native String getString(long ptr);
    public static native String getStringOffset(long ptr,int offset);

    public static native void setPointer(long ptr,long value);
    public static native void setPointerOffset(long ptr,int offset,long value);
    public static native void setInt(long ptr,int value);
    public static native void setIntOffset(long ptr,int offset,int value);
    public static native void setFloat(long ptr,float value);
    public static native void setFloatOffset(long ptr,int offset,float value);
    public static native void setBool(long ptr,boolean value);
    public static native void setBoolOffset(long ptr,int offset,boolean value);
    public static native void setString(long ptr,String value);
    public static native void setStringOffset(long ptr,int offset,String value);
}
