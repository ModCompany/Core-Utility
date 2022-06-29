package com.core.api.module;

import com.core.api.engine.PointerClass;

public class ItemsUtil {
    native public static long getItemById(int id);

    public static PointerClass getItem(int id){
        return new PointerClass(id);
    }
}
