package com.core.api.dungeonutility.struct;

import com.core.api.dungeonutility.api.BlockData;
import com.core.api.engine.PointerClass;
import com.zhekasmirnov.apparatus.mcpe.NativeBlockSource;

public class StructureObject extends PointerClass {
    native public static long newStructureObject();
    native public static void addBlock(long pointer, long block);
    native public static void set(long pointer, int x, int y, int z, long region);

    public StructureObject(){
        super(newStructureObject());
    }

    public StructureObject(long pointer){
        super(pointer);
    }

    public StructureObject addBlock(BlockData block){
        addBlock(pointer, block.getPointer());
        return this;
    }

    public StructureObject set(int x, int y, int z, NativeBlockSource region){
        set(pointer, x, y, z, region.getPointer());
        return this;
    }
}
