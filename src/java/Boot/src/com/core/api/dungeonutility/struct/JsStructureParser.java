package com.core.api.dungeonutility.struct;

public class JsStructureParser extends StructureParser {
    public static interface JS {
        String save(StructureObject object);
        StructureObject read(String object);
    }

    JS js;

    public JsStructureParser(JS js){
        super(0);
        this.js = js;
    }

    @Override
    public String save(StructureObject object) {
        return js.save(object);
    }

    @Override
    public StructureObject read(String text) {
        return js.read(text);
    }
}
