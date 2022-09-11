package com.core.api.dungeonutility.struct;

import com.core.api.dungeonutility.StructureCompile;
import com.core.api.engine.PointerClass;
import com.zhekasmirnov.innercore.api.mod.adaptedscript.AdaptedScriptAPI.FileUtil;
import com.zhekasmirnov.innercore.api.runtime.Callback;

public class StructurePool extends PointerClass {
    native public static void levelPreLoaded();
    native public static long newStructurePool();
    native public static void registerStructurePool(String name, long pool);
    native public static long get(long pointer, String name);
    native public static void put(long pointer, String name, long structure);
    native public static void load(long pointer, String text, String name, String type);
    native public static void loadRuntime(long pointer, String text, String name, String type);

    public static void preLoadStructure(){
        Callback.invokeCallback("StrcturePreLoad", new Object[] {});
    }

    public static void loadStructure(){
        Callback.invokeCallback("StrctureLoad", new Object[] {});
    }


    public StructurePool(long pointer) {
        super(pointer);
    }

    public StructurePool(String name){
        this(newStructurePool());
        registerStructurePool(name, pointer);
    }

    public StructurePool(){
        this(newStructurePool());
    }

    public StructureObject get(String name){
        return new StructureObject(get(pointer, name));
    }

    public StructurePool put(String name, StructureObject structure){
        put(pointer, name, structure.getPointer());
        return this;
    }

    public StructurePool load(String path, String name, String type, boolean haffman){
        if(haffman)
            load(pointer, StructureCompile.decompile(path), name, type);
        else
            load(pointer, FileUtil.readFileText(path), name, type);
        return this;
    }
    public StructurePool loadRuntime(String path, String name, String type, boolean haffman){
        if(haffman)
            loadRuntime(pointer, StructureCompile.decompile(path), name, type);
        else
            loadRuntime(pointer, FileUtil.readFileText(path), name, type);
        return this;
    }
}
