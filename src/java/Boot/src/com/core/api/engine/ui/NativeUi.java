package com.core.api.engine.ui;

import com.core.api.engine.ui.types.Element;

public class NativeUi {
    long ptr;
    public NativeUi(Element[] elements){
        ptr = init(elements);
    }
    public NativeUi(){
        this(new Element[] {});
    }

    public boolean isOpen(){
        return isOpen(ptr);
    }

    public NativeUi open(){
        open(ptr);
        return this;
    }

    public NativeUi close(){
        close(ptr);
        return this;
    }
    
    static public native Element[] getElements(long ptr);
    static public native void setElements(long ptr, Element[] elements);
    static public native void setPriority(long ptr, int priority);
    static public native void open(long ptr);
    static public native void close(long ptr);
    static public native boolean isOpen(long ptr);
    static public native void free();
    static public native long init(Element[] elements);
}
