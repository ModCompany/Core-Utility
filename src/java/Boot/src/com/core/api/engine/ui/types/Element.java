package com.core.api.engine.ui.types;

public class Element {
    public int x, y;
    public String material;
    public Element(int x, int y, String material){
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
    public int getX(){
        return x;
    }
    public int getY(){
        return y;
    }
}
