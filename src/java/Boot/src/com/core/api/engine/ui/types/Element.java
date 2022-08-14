package com.core.api.engine.ui.types;

public class Element {
    public int x, y;
    public Element(int x, int y){
        this.x = x;
        this.y = y;
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
