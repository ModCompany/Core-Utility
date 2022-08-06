package com.core.api.mcpe.api;

import com.core.api.engine.PointerClass;

public class ChunkPos extends PointerClass {
    native public static long newClass(int x, int y);
    native public static void setX(long ptr, int x);
    native public static void setZ(long ptr, int x);
    native public static int getX(long ptr);
    native public static int getZ(long ptr);
    native public static void free(long ptr);

    boolean freeEnable;
    public ChunkPos(int x, int y){
        super(newClass(x, y));
        freeEnable = true;
    }
    public ChunkPos(long ptr){
        super(ptr);
        freeEnable = false;
    }

    public int getX(){
        return getX(pointer);
    }
    public int getZ(){
        return getZ(pointer);
    }

    public void setX(int x){
        setX(pointer, x);
    }

    public void setY(int x){
        setX(pointer, x);
    }

    boolean isFree = false;
    public void free(){
        if(!isFree)
            free(this.pointer);
        isFree = true;
    }

    @Override
    public void finalize() {
        if(freeEnable)
            free();
    }
}
