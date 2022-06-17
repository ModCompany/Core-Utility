package com.core.api.mcpe.api;

public class Vec3 {
    native public static long newClass(float x, float y, float z);
    native public static void setX(long ptr, float x);
    native public static void setY(long ptr, float x);
    native public static void setZ(long ptr, float x);
    native public static float getX(long ptr);
    native public static float getY(long ptr);
    native public static float getZ(long ptr);
    native public static void free(long ptr);

    long ptr;
    public Vec3(float x, float y, float z){
        this.ptr = newClass(x, y, z);
    }
    public Vec3(long ptr){
        this.ptr = ptr;
    }
    public long getPointer(){
        return ptr;
    }

    public float getX(){
        return getX(ptr);
    }
    public float getY(){
        return getY(ptr);
    }
    public float getZ(){
        return getZ(ptr);
    }

    public void setX(float x){
        setX(ptr, x);
    }

    public void setY(float x){
        setX(ptr, x);
    }

    public void setZ(float x){
        setZ(ptr, x);
    }

    public void free(){
        free(ptr);
    }
}
