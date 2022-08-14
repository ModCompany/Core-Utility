package com.core.api.engine.ui.types;

import org.mozilla.javascript.ScriptableObject;

public class TextElement extends Element {
    int size;
    String text;
    public TextElement(int x, int y, String material, String text, int size){
        super(x, y, material);
        this.text = text;
        this.size = size;
    }
    public TextElement(ScriptableObject object){
        this(
            ((Double) object.get("x")).intValue(),
            ((Double) object.get("y")).intValue(),
            object.has("material", object) ? ((String) object.get("material")) : "ui_textured_and_glcolor",
            ((String) object.get("text")),
            object.has("size", object) ? ((Double) object.get("size")).intValue() : 100
        );
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
