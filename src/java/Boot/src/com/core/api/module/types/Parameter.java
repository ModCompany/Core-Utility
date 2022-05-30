package com.core.api.module.types;

public class Parameter {
    String type; Object v;
    public Parameter(long v, String type){
        this.type = type;
        this.v = v;
    }
    public Parameter(int v, String type){
        this.type = type;
        this.v = v;
    }
    public Parameter(float v, String type){
        this.type = type;
        this.v = v;
    }
    public Parameter(String v, String type){
        this.type = type;
        this.v = v;
    }

    public Object getValue(){
        if(type == "bool")
            return ((Integer) v).intValue() == 1;
        return v;
    }
}
