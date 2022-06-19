package com.core.api.mcpe.level;

import com.core.api.engine.PointerClass;
import com.core.api.mcpe.api.Random;
import com.zhekasmirnov.apparatus.mcpe.NativeBlockSource;

public class LevelServer extends PointerClass{
    public LevelServer(long pointer){
        super(pointer);
    }

    public Random getRandom(){
        return new Random(Level.getRandomPointer(pointer));
    }

    public void addEntity(NativeBlockSource region, float x, float y, float z, String name){
        Level.addEntityLevel(region.getPointer(), x, y, z, name);
    }
}
