package com.core.api.engine.ui.types;

public class ImageElement extends Element {
    public int width, heigth;
    String texture;
    public ImageElement(String texture, int x, int y, int width, int heigth){
        super(x, y);
        this.width = width;
        this.heigth = heigth;
        this.texture = texture;
    }
    @Override
    String getType() {
        return "image";
    }
    public int getHeigth() {
        return heigth;
    }
    public int getWidth() {
        return width;
    }
    public String getTexture() {
        return texture;
    }
}