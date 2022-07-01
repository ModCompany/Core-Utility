package com.core.api.engine;

import java.util.ArrayList;

import org.mozilla.javascript.Function;

import com.core.api.JsHelper;
import com.core.api.mcpe.level.LevelData;
import com.zhekasmirnov.horizon.runtime.logger.Logger;
import com.zhekasmirnov.innercore.api.nbt.NativeCompoundTag;

public class NativeSaver {
    public static ArrayList<NativeSaver> savers = new ArrayList<>();
    public String name;
    public Function read, save;
    public NativeSaver(String name){
        this.name = name;
    }
    public NativeSaver read(Function read){
        this.read = read;
        return this;
    }
    public NativeSaver save(Function save){
        this.save = save;
        return this;
    }

    public static void saveCallback(long levelData, long tag){
        Logger.debug("SAVE: "+tag);
        if(tag != 0){
            Object[] args = {new LevelData(levelData), new NativeCompoundTag(tag)};
            for (NativeSaver nativeSaver : savers)
                if(nativeSaver.save != null)
                    JsHelper.callFunction(nativeSaver.save, args);
        }
    }
    public static void readCallback(long levelData, long tag){
        Logger.debug("READ");
        Object[] args = {new LevelData(levelData), new NativeCompoundTag(tag)};
        for (NativeSaver nativeSaver : savers)
            if(nativeSaver.read != null)
                JsHelper.callFunction(nativeSaver.read, args);
    }
}
