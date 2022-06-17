package com.core.api.mcpe.api;

public class Vec2 {
    native public static long newClass(float x, float y);
    native public static void setX(long ptr, float x);
    native public static void setY(long ptr, float x);
    native public static float getX(long ptr);
    native public static float getY(long ptr);
    native public static void free(long ptr);

    long ptr;
    public Vec2(float x, float y){
        this.ptr = newClass(x, y);
    }
    public Vec2(long ptr){
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

    public void setX(float x){
        setX(ptr, x);
    }

    public void setY(float x){
        setX(ptr, x);
    }

    public void free(){
        free(ptr);
    }
}
