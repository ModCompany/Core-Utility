package com.core.api.engine;

public class NativeVar extends PointerClass {//не большая заготовка на будующие
    public static abstract class NativeType {}
    native static void registerType(String name, NativeType type);
    native public static long init();

    public NativeVar(Object value, String type){
        super(init());
        setSelf(this);
        setType(type);
        set(value);
    }

    native private void setSelf(Object name); 
    native private void setType(String name); 
    native public Object get();
    native public void set(Object value);
    @Override
    native public void finalize();
}