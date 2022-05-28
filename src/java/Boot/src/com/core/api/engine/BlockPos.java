package com.core.api.engine;

public class BlockPos extends NativeJavaObject {

    public BlockPos(int a,int b,int c){
        super();
        Object[] o ={a,b,c};
        this.object = o;
        this.args_count = this.object.length;

    }
    @Override
    public String getType() {
        return "BlockPos";
    }
}
