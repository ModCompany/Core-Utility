package com.core.api.mcpe.api;

import com.core.api.engine.PointerClass;

public class Vec2 extends PointerClass{
    native public static long newClass(float x, float y);
    native public static void setX(long ptr, float x);
    native public static void setY(long ptr, float x);
    native public static float getX(long ptr);
    native public static float getY(long ptr);
    native public static void free(long ptr);

    boolean freeEnable;
    public Vec2(float x, float y){
        super(newClass(x, y));
        freeEnable = true;
    }
    public Vec2(long ptr){
        super(ptr);
        freeEnable = false;
    }

    public float getX(){
        return getX(pointer);
    }
    public float getY(){
        return getY(pointer);
    }

    public void setX(float x){
        setX(pointer, x);
    }

    public void setY(float x){
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
