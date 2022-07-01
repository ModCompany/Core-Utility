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
    public void read(Function read){
        this.read = read;
    }
    public void save(Function save){
        this.save = save;
    }

    public static void save(long levelData, long tag){
        Logger.debug("SAVE");
        Object[] args = {new LevelData(levelData), new NativeCompoundTag((long) tag)};
        for (NativeSaver nativeSaver : savers)
            if(nativeSaver.save != null)
                JsHelper.callFunction(nativeSaver.save, args);
    }
    public static void read(long levelData, long tag){
        Logger.debug("READ");
        Object[] args = {new LevelData(levelData), new NativeCompoundTag((long) tag)};
        for (NativeSaver nativeSaver : savers)
            if(nativeSaver.read != null)
                JsHelper.callFunction(nativeSaver.read, args);
    }
}
