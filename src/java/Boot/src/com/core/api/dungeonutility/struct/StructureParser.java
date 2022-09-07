package com.core.api.dungeonutility.struct;

import com.core.api.engine.PointerClass;

public class StructureParser extends PointerClass {
    native public static String save(long parser, long structure);
    native public static long read(long parser, String structure);

    native public static void registerFormat(String name, StructureParser parser);
    native public static boolean canParser(String name);
    native public static long nativeGetParser(String name);
    public static StructureParser getParser(String name){
        if(canParser(name))
            return new StructureParser(nativeGetParser(name));
        return new StructureParser();
    }

    public StructureParser(long pointer){
        super(pointer);
    }

    public StructureParser(){
        this(0);
    }

    public String nativeSave(long ptr){
        return save(new StructureObject(ptr));
    }
    public long nativeRead(String str){
        return read(str).getPointer();
    }
    public String save(StructureObject object){
        if(pointer != 0)
            return save(pointer, object.getPointer());
        return "";
    }

    public StructureObject read(String text){
        if(pointer != 0)
            return new StructureObject(read(pointer, text));
        return new StructureObject();
    }
}
