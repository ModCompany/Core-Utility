package com.core.api.mcpe.level;

import com.core.api.mcpe.api.Random;
import com.zhekasmirnov.apparatus.mcpe.NativeBlockSource;

public class Level {
    public static native int getCurrentTick();
    public static native int getCurrentServerTick();
    public static native int getChunkTickRange();
    native public static long getRandomPointer(long pointer);
    native public static void addEntityLevel(long pointer, float x, float y, float z, String name);

    long pointer;
    public Level(long pointer){
        this.pointer = pointer;
    }

    public long getPointer(){
        return pointer;
    }

    public Random getRandom(){
        return new Random(getRandomPointer(pointer));
    }

    public void addEntity(NativeBlockSource region, float x, float y, float z, String name){
        addEntityLevel(region.getPointer(), x, y, z, name);
    }
}