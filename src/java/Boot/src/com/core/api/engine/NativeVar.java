package com.core.api.engine;

public class NativeVar extends PointerClass {
    native public static long init();

    native private static void nativeSetType(long ptr, String name); 
    native private static Object nativeGet(long ptr);
    native private static void nativeSet(long ptr, Object value);
    native private static void nativeFree(long ptr);
    native private static void nativeSetFinalize(long ptr, boolean value);
    native private static void nativeFinalize(long ptr);

    public NativeVar(long ptr){
        super(ptr);
    }
    public NativeVar(Object value, String type){
        this(init());
        setType(type);
        set(value);
    }

    public NativeVar setType(String type){
        nativeSetType(pointer, type);
        return this;
    }

    public Object get(){
        return nativeGet(pointer);
    }

    public NativeVar set(Object value){
        nativeSet(pointer, value);
        return this;
    }

    @Override
    public void free(){
        nativeFree(pointer);
    }

    public NativeVar setFinalize(boolean enable){
        nativeSetFinalize(pointer, enable);
        return this;
    }

    @Override
    protected void finalize() throws Throwable {
        nativeFinalize(pointer);
    }
}