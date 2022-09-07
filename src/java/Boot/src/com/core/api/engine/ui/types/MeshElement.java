package com.core.api.engine.ui.types;

import org.mozilla.javascript.ScriptableObject;

import com.zhekasmirnov.innercore.api.NativeRenderMesh;


public class MeshElement extends Element {
    public float z;
    public NativeRenderMesh mesh;
    public String texture;
    public MeshElement(float x, float y, float z, String material, NativeRenderMesh mesh, String texture) {
        super(x, y, material);
        this.z = z;
        mesh.setNoTint();
        mesh.setLightIgnore(true, true);
        this.mesh = mesh;
        this.texture = texture;
    }
    
    public MeshElement(ScriptableObject object){
        this(
            ((Double) object.get("x")).floatValue(), 
            ((Double) object.get("y")).floatValue(), 
            object.has("z", object) ? ((Double) object.get("z")).floatValue() : 0,
            object.has("material", object) ? ((String) object.get("material")) : "native_ui_mesh",
            (NativeRenderMesh) object.get("mesh"),
            object.has("texture", object) ? ((String) object.get("texture")) : "terrain::atlas"
        );
    }

    public float getZ() {
        return z;
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
