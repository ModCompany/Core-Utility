package com.core.api.engine;

public class NativeVar extends PointerClass {
    native public static long init();

    public NativeVar(long ptr){
        super(ptr);
    }
    public NativeVar(Object value, String type){
        this(init());
        setType(type);
        set(value);
    }

    native private void setType(String name); 
    native public Object get();
    native public void set(Object value);
    native public void free();
    native public void setFinalize(boolean value);
    @Override
    native public void finalize();
}