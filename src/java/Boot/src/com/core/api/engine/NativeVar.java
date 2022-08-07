package com.core.api.engine;

import java.lang.reflect.Constructor;

public class NativeVar extends PointerClass {
    native static void registerType(String name, Constructor<PointerClass> type);
    native public static long init();

    public NativeVar(Object value, String type){
        super(init());
        setType(type);
       /*  if(type == "int" && value instanceof Double)
            set(((Double) value).intValue());
        else
            set(value);*/
    }

    native private void setType(String name); 
    native public Object get();
    native public void set(Object value);
    native public void free();
    native public void setFinalize(boolean value);
    @Override
    native public void finalize();
}