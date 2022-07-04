package com.core.api.mcpe.level;

import com.core.api.engine.PointerClass;

public class LevelData extends PointerClass {
    public LevelData(long ptr){
        super(ptr);
    }

    public void setSeed(int seed){
        setSeed(this.getPointer(), seed);
    }

    public int getSeed(){
        return getSeed(this.getPointer());
    }
    
    public static native void setSeed(long pointer,int seed);
    public static native int getSeed(long pointer);
}
