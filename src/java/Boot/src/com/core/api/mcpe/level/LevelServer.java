package com.core.api.mcpe.level;

import com.core.api.mcpe.api.Random;

public class LevelServer {
    long pointer;
    public LevelServer(long pointer){
        this.pointer = pointer;
    }

    public long getPointer(){
        return pointer;
    }

    public Random getRandom(){
        return new Random(Level.getRandomPointer(pointer));
    }
}
