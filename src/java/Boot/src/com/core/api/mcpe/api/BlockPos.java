package com.core.api.mcpe.api;

import com.core.api.module.NativeAPI;

public class BlockPos {
    native public static long newClass(int x, int y, int z);
    native public static void setX(long ptr, int x);
    native public static void setY(long ptr, int x);
    native public static void setZ(long ptr, int x);
    native public static void free(long ptr);

    long ptr;
    public BlockPos(int x, int y, int z){
        this.ptr = newClass(x, y, z);
    }
    public BlockPos(long ptr){
        this.ptr = ptr;
    }
    public long getPointer(){
        return ptr;
    }

    public int getX(){
        return NativeAPI.getXBlockPos(ptr);
    }

    public int getY(){
        return NativeAPI.getYBlockPos(ptr);
    }

    public int getZ(){
        return NativeAPI.getZBlockPos(ptr);
    }

    public void setX(int x){
        setX(ptr, x);
    }
    public void setY(int x){
        setY(ptr, x);
    }
    public void setZ(int x){
        setZ(ptr, x);
    }
    public void free(){
        free(ptr);
    }
}
