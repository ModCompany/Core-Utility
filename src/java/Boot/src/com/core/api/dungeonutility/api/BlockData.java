package com.core.api.dungeonutility.api;

import com.core.api.engine.PointerClass;
import com.zhekasmirnov.apparatus.adapter.innercore.game.block.BlockState;

public class BlockData extends PointerClass {
    native public static long getPointerToBlock(int id, int data, int rutimeid);

    public static long getPointerBlock(BlockState state){
        return getPointerToBlock(state.id, state.data, state.runtimeId);
    }

    native public static long newBlockData(int x, int y, int z, long block, long extra);

    public BlockData(int x, int y, int z, BlockState block, BlockState extra){
        super(newBlockData(x, y, z, getPointerBlock(block), getPointerBlock(extra)));
    }
}
