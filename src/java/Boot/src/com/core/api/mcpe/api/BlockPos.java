package com.core.api.mcpe.api;

import com.core.api.engine.PointerClass;
import com.core.api.module.NativeAPI;

public class BlockPos extends PointerClass {
    native public static long newClass(int x, int y, int z);
    native public static void setX(long ptr, int x);
    native public static void setY(long ptr, int x);
    native public static void setZ(long ptr, int x);
    native public static void free(long ptr);

    public BlockPos(int x, int y, int z){
        super(newClass(x, y, z));
    }
    public BlockPos(long ptr){
        super(ptr);
    }

    public int getX(){
        return NativeAPI.getXBlockPos(pointer);
    }

    public int getY(){
        return NativeAPI.getYBlockPos(pointer);
    }

    public int getZ(){
        return NativeAPI.getZBlockPos(pointer);
    }

    public void setX(int x){
        setX(pointer, x);
    }
    public void setY(int x){
        setY(pointer, x);
    }
    public void setZ(int x){
        setZ(pointer, x);
    }
    public void free(){
        free(pointer);
    }
}
