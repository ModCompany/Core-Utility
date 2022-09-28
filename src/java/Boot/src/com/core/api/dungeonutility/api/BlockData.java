package com.core.api.dungeonutility.api;

import com.core.api.engine.PointerClass;
import com.zhekasmirnov.apparatus.adapter.innercore.game.block.BlockState;

public class BlockData extends PointerClass {
    native public static long getPointerToBlock(int id, int data, int rutimeid);
    native public static long getBlock(long pointer);
    native public static long getBlockExtra(long pointer);
    native public static int getX(long pointer);
    native public static int getY(long pointer);
    native public static int getZ(long pointer);

    public static long getPointerBlock(BlockState state){
        return getPointerToBlock(state.id, state.data, state.runtimeId);
    }

    native public static long newBlockData(int x, int y, int z, long block, long extra);

    public BlockData(int x, int y, int z, BlockState block, BlockState extra){
        this(newBlockData(x, y, z, getPointerBlock(block), getPointerBlock(extra)));
    }
    public BlockData(long ptr){
        super(ptr);
    }

    public BlockState getState(){
        return new BlockState(getBlock(pointer));
    }

    public BlockState getStateExtra(){
        return new BlockState(getBlockExtra(pointer));
    }

    public int getX(){
        return getX(pointer);
    }

    public int getY(){
        return getY(pointer);
    }

    public int getZ(){
        return getZ(pointer);
    }

    public static BlockData createData(int x, int y, int z, BlockState block, BlockState extra){
        return new BlockData(x, y, z, block, extra);
    }

    public static BlockData createData(int x, int y, int z, BlockState block){
        return new BlockData(x, y, z, block, new BlockState(0, 0));
    }
}
