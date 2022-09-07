package com.core.api.innnercore;

import java.util.HashMap;

import com.core.api.dungeonutility.api.BlockData;
import com.core.api.mcpe.block.Block;
import com.core.api.mcpe.block.BlockLegacy;
import com.zhekasmirnov.apparatus.adapter.innercore.game.block.BlockState;
import com.zhekasmirnov.innercore.api.NativeBlockRenderer;
import com.zhekasmirnov.innercore.api.NativeICRender;

public class BlockUtils {
    native public static long getBlockLegacy(int id);
    native public static long getBlockState(int id, int data);

    public static BlockLegacy getBlockById(int id){
        return new BlockLegacy(getBlockLegacy(id));
    }
    public static Block getBlockStateForIdData(int id, int data){
        return new Block(getBlockState(id, data));
    }
    public static Block getBlock(BlockState state){
        return new Block(BlockData.getPointerBlock(state));
    }
        

    public static HashMap<Integer, NativeICRender.Model> models = new HashMap<>();
    public static void register(int id, NativeICRender.Model model){
        models.put(id , model);
        NativeBlockRenderer.enableCoordMapping(id, -1, model);
    }
    

    public static void renderModelBlock(long mesh, long bl, long po){
    }
}
