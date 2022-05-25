package com.core.api.mcpe.level;

import com.core.api.mcpe.api.Random;

public class Level {
    public static native int getCurrentTick();
    public static native int getCurrentServerTick();
    public static native int getChunkTickRange();
    native public static long getRandomPointer(long pointer);

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
}