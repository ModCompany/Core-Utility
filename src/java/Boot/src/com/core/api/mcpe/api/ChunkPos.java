package com.core.api.mcpe.api;

public class ChunkPos {
    native public static long newClass(int x, int y);
    native public static void setX(long ptr, int x);
    native public static void setZ(long ptr, int x);
    native public static int getX(long ptr);
    native public static int getZ(long ptr);
    native public static void free(long ptr);

    long ptr;
    public ChunkPos(int x, int y){
        this.ptr = newClass(x, y);
    }
    public ChunkPos(long ptr){
        this.ptr = ptr;
    }
    public long getPointer(){
        return ptr;
    }

    public int getX(){
        return getX(ptr);
    }
    public int getZ(){
        return getZ(ptr);
    }

    public void setX(int x){
        setX(ptr, x);
    }

    public void setY(int x){
        setX(ptr, x);
    }

    public void free(){
        free(ptr);
    }
}
