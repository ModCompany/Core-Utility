package com.core.api.engine;

import com.core.api.Injector;

public class CppClass extends PointerClass {
    protected Injector injector;
    protected DataOffset offset;

    public CppClass(long pointer) {
        super(pointer);

        injector = new Injector(pointer);
        offset = injector.getData();
    }

    public Injector getInjector() {
        return injector;
    }

    public DataOffset getOffset() {
        return offset;
    }

    @Override
    public void free() {
        injector.free();
        offset.free();
    }

    public void deconstructor(String symbol){
        injector.setArgsTypes().apply(symbol);
        free();
    }
}