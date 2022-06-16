package com.core.api.module.types;

import com.core.api.mcpe.api.BlockPos;
import com.zhekasmirnov.horizon.runtime.logger.Logger;

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
        if(type.equals("bool"))
            return ((Integer) v).intValue() == 1;
        else if(type.equals("BlockPos"))
            return new BlockPos((long) v);
        return v;
    }
}
