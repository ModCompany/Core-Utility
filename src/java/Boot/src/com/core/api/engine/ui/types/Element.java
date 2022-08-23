package com.core.api.engine.ui.types;

public class Element {
    public float x, y;
    public String material;
    public Element(float x, float y, String material){
        this.x = x;
        this.y = y;
        this.material = material;
    }
    public String getMaterial() {
        return material;
    }
    String getType(){
        return "null";
    }
    public float getX(){
        return x;
    }
    public float getY(){
        return y;
    }
    public boolean isTouch(float x, float y){
        return false;
    }
}
