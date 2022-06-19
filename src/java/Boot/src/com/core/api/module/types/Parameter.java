package com.core.api.module.types;

import com.core.api.mcpe.api.BlockPos;
import com.core.api.mcpe.api.ChunkPos;
import com.core.api.mcpe.api.Vec2;
import com.core.api.mcpe.api.Vec3;
import com.zhekasmirnov.apparatus.mcpe.NativeBlockSource;
import com.zhekasmirnov.innercore.api.nbt.NativeCompoundTag;

public class Parameter {
    public static Parameter getInt(int v){
        return new Parameter(v, "int");
    }

    public static Parameter getFloat(float v){
        return new Parameter(v, "float");
    }

    public static Parameter getBool(boolean v){
        return new Parameter(v ? 1 : 0, "bool");
    }

    public static Parameter getPointer(long v){
        return new Parameter(v, "ptr");
    }

    public static Parameter getString(String v){
        return new Parameter(v, "stl::string");
    }

    String type; Object v;
    public Parameter(long v, String type){
        this.type = type;
        this.v = v;
    }
    public Parameter(int v, String type){
        this.type = type;
        this.v = v;
    }
    public Parameter(float v, String type){
        this.type = type;
        this.v = v;
    }
    public Parameter(String v, String type){
        this.type = type;
        this.v = v;
    }

    public long getPointer(){
        return (long) v;
    }

    public int getInt(){
        return (int) v;
    }

    public float getFloat(){
        return (float) v;
    }

    public String getString(){
        return (String) v;
    }

    public Object getValue(){
        if(type.equals("bool"))
            return ((int) v) == 1;
        else if(type.equals("BlockPos"))
            return new BlockPos((long) v);
        else if(type.equals("Vec2"))
            return new Vec2((long) v);
        else if(type.equals("Vec3"))
            return new Vec3((long) v);
        else if(type.equals("ChunkPos"))
            return new ChunkPos((long) v);
        else if(type.equals("BlockSource"))
            return NativeBlockSource.getFromCallbackPointer((long) v);
        else if(type.equals("CompoundTag"))
            return new NativeCompoundTag((long) v);
        return v;
    }
}
