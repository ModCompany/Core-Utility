package com.core.api.innnercore;

import com.core.api.engine.PointerClass;
import com.core.api.mcpe.block.BlockLegacy;

public class BlockUtils {
    native public static long getBlockLegacy(int id);
    native public static long getBlockState(int id, int data);

    public static BlockLegacy getBlockById(int id){
        return new BlockLegacy(getBlockLegacy(id));
    }
    public static PointerClass getBlockStateForIdData(int id, int data){
        return new PointerClass(getBlockState(id, data));
    }
}
