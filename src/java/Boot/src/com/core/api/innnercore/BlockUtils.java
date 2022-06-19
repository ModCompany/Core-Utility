package com.core.api.innnercore;

import com.core.api.engine.PointerClass;

public class BlockUtils {
    native public static long getBlockLegacy(int id);
    native public static long getBlockState(int id, int data);

    public static PointerClass getBlockById(int id){
        return new PointerClass(getBlockLegacy(id));
    }
    public static PointerClass getBlockStateForIdData(int id, int data){
        return new PointerClass(getBlockState(id, data));
    }
}
