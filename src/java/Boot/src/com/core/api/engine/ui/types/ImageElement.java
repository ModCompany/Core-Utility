package com.core.api.engine.ui.types;

import org.mozilla.javascript.ScriptableObject;

public class ImageElement extends Element {
    public int width, height, tex_w, tex_h;
    public String texture;
    public ImageElement(String texture, float x, float y, int width, int heigth, int tex_w, int tex_h, String material){
        super(x, y, material);
        this.width = width;
        this.height = heigth;
        this.texture = texture;
        this.tex_w = tex_w;
        this.tex_h = tex_h;
    }
    public ImageElement(ScriptableObject object){
        this(
            (String) object.get("texture"), 
            ((Double) object.get("x")).floatValue(),
            ((Double) object.get("y")).floatValue(),
            ((Double) object.get("width")).intValue(),
            ((Double) object.get("height")).intValue(),
            object.has("texture_width", object) ? ((Double) object.get("texture_width")).intValue() : ((Double) object.get("width")).intValue(),
            object.has("texture_height", object) ? ((Double) object.get("texture_height")).intValue() : ((Double) object.get("height")).intValue(),
            object.has("material", object) ? ((String) object.get("material")) : "ui_textured_and_glcolor"
        );
    }
    @Override
    String getType() {
        return "image";
    }
    public int getHeight() {
        return height;
    }
    public int getWidth() {
        return width;
    }
    public String getTexture() {
        return texture;
    }
    public int getTextureWidth() {
        return tex_w;
    }
    public int getTextureHeight() {
        return tex_h;
    }
    @Override
    public boolean isTouch(float x, float y){
        return (this.x <= x && this.y <= y) && (x <= this.x + width && y <= this.y + height);
    }
}