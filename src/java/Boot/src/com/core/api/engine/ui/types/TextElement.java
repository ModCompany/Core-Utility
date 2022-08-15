package com.core.api.engine.ui.types;

import org.mozilla.javascript.ScriptableObject;

public class TextElement extends Element {
    int size, shadow_offset, font_type;
    String text;
    boolean shadow;
    public TextElement(int x, int y, String material, String text, int size, boolean shadow, int shadow_offset, int font_type){
        super(x, y, material);
        this.text = text;
        this.size = size;
        this.shadow = shadow;
        this.shadow_offset = shadow_offset;
        this.font_type = font_type;
    }
    public TextElement(ScriptableObject object){
        this(
            ((Double) object.get("x")).intValue(),
            ((Double) object.get("y")).intValue(),
            object.has("material", object) ? ((String) object.get("material")) : "ui_text",
            ((String) object.get("text")),
            object.has("size", object) ? ((Double) object.get("size")).intValue() : 100,
            object.has("shadow", object) ? ((Boolean) object.get("shadow")).booleanValue() : false,
            object.has("shadow_offset", object) ? ((Double) object.get("shadow_offset")).intValue() : 1,
            object.has("font_type", object) ? ((Double) object.get("font_type")).intValue() : 0
        );
    }

    public int getFontType() {
        return font_type;
    }

    public int getShadowOffset() {
        return shadow_offset;
    }

    public boolean isShadow() {
        return shadow;
    }

    public String getText() {
        return text;
    }

    public int getSize() {
        return size;
    }

    @Override
    String getType() {
        return "text";
    }
}
