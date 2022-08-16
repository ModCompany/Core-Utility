package com.core.api.engine.ui.types;

import org.mozilla.javascript.ScriptableObject;

import com.zhekasmirnov.innercore.api.NativeRenderMesh;


public class MeshElement extends Element {
    public NativeRenderMesh mesh;
    public String texture;
    public MeshElement(float x, float y, String material, NativeRenderMesh mesh, String texture) {
        super(x, y, material);
        this.mesh = mesh;
        this.texture = texture;
    }
    
    public MeshElement(ScriptableObject object){
        this(
            ((Double) object.get("x")).floatValue(), 
            ((Double) object.get("y")).floatValue(), 
            object.has("material", object) ? ((String) object.get("material")) : "ui_textured_and_glcolor",
            (NativeRenderMesh) object.get("mesh"),
            object.has("texture", object) ? ((String) object.get("texture")) : "terrain-atlas"
        );
    }

    @Override
    String getType() {
        return "mesh";
    }

    public long getMesh() {
        return mesh.getPtr();
    }

    public String getTexture() {
        return texture;
    }
}
