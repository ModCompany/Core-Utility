package com.core.api.engine;

public abstract class NativeJavaObject {
    
    public Object[] object;
    public int args_count;
    public NativeJavaObject(){
    }

    public Object[] getObject(){
        return object;
    }

    public int getArgsCount(){
        return args_count;
    }
    
    public abstract String getType();
}
