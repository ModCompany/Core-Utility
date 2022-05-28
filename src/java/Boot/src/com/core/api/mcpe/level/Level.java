package com.core.api.mcpe.level;

import com.core.api.mcpe.api.Random;
import com.zhekasmirnov.apparatus.mcpe.NativeBlockSource;

public class Level {
    public static native int getCurrentTick(long pointer);
    public static native int getCurrentServerTick(long pointer);
    public static native int getChunkTickRange(long pointer);
    public static native long getRandomPointer(long pointer);
    public static native void addEntityLevel(long pointer, float x, float y, float z, String name);

    long pointer;
    public Level(long pointer){
        this.pointer = pointer;
    }

    public void addEntity(NativeBlockSource region, float x, float y, float z, String name){
        addEntityLevel(region.getPointer(), x, y, z, name);
    }

    public int getCurrentTick(){
        return getCurrentTick(this.pointer);
    }

    public int getCurrentServerTick(){
        return getCurrentServerTick(this.pointer);
    }

    public int getChunkTickRange(){
        return getChunkTickRange(this.pointer);
    }
    
    public Random getRandom(){
        return new Random(getRandomPointer(pointer));
    }

    public long getPointer(){
        return pointer;
    }
}