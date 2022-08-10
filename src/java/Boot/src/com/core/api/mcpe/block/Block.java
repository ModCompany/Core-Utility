package com.core.api.mcpe.block;

import com.core.api.Injector;
import com.core.api.engine.PointerClass;
import com.zhekasmirnov.apparatus.adapter.innercore.game.block.BlockState;

public class Block extends PointerClass {
    Injector injector;
    public Block(long ptr){
        super(ptr);
        injector = new Injector(ptr);
    }

    public int getRuntimeId(){
        return injector.setArgsTypes(new String[]{}).getIntResult("_ZNK5Block12getRuntimeIdEv");
    }
}
