package com.core.api.module;

import com.core.api.engine.PointerClass;
import com.core.api.mcpe.item.Item;

public class ItemsUtil {
    native public static long getItemById(int id);

    public static PointerClass getItem(int id){
        return new Item(id);
    }
}
