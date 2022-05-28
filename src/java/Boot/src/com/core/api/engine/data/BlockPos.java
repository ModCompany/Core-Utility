package com.core.api.engine.data;

import com.core.api.engine.NativeJavaObject;

public class BlockPos extends NativeJavaObject {

    public BlockPos(int a,int b,int c){
        super(a,b,c);
    }
    
    @Override
    public String getType() {
        return "BlockPos";
    }
}
