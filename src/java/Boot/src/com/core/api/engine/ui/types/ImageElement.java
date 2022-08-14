package com.core.api.engine.ui.types;

import org.mozilla.javascript.ScriptableObject;

public class ImageElement extends Element {
    public int width, heigth, tex_w, tex_h;
    String texture;
    public ImageElement(String texture, int x, int y, int width, int heigth, int tex_w, int tex_h){
        super(x, y);
        this.width = width;
        this.heigth = heigth;
        this.texture = texture;
        this.tex_w = tex_w;
        this.tex_h = tex_h;
    }
    public ImageElement(ScriptableObject object){
        this(
            (String) object.get("texture"), 
            ((Double) object.get("x")).intValue(),
            ((Double) object.get("y")).intValue(),
            ((Double) object.get("width")).intValue(),
            ((Double) object.get("heigth")).intValue(),
            object.has("texture_width", object) ? ((Double) object.get("texture_width")).intValue() : ((Double) object.get("width")).intValue(),
            object.has("texture_heigth", object) ? ((Double) object.get("texture_heigth")).intValue() : ((Double) object.get("heigth")).intValue()
        );
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
    public int getTextureWidth() {
        return tex_w;
    }
    public int getTextureHeigth() {
        return tex_h;
    }
}