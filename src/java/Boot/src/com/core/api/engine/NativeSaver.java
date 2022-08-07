package com.core.api.engine;

import java.util.ArrayList;

import org.mozilla.javascript.Function;

import com.core.api.JsHelper;
import com.zhekasmirnov.horizon.runtime.logger.Logger;
import com.zhekasmirnov.innercore.api.log.DialogHelper;
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

    private static NativeCompoundTag getSaverTag(String name, NativeCompoundTag tag){
        if(!tag.contains(name)){
            NativeCompoundTag _tag = new NativeCompoundTag();
            _tag.setFinalizable(false);
            tag.putCompoundTag(name, _tag);
        }
        return tag.getCompoundTag(name);
    }

    public static void saveCallback(long player, long tag){
        Logger.debug(player+" "+tag, "Test");
        NativeCompoundTag _tag = new NativeCompoundTag(tag);
        _tag.setFinalizable(false);
        Object[] args = {player, null};
        for (NativeSaver nativeSaver : savers){
            try {
                args[1] = getSaverTag(nativeSaver.name, _tag);
                if(nativeSaver.save != null)
                    JsHelper.callFunction(nativeSaver.save, args);
            } catch (Exception e) {
                
                //Logger.error("NativeSaver, save: "+nativeSaver.name, e.getCause());
                DialogHelper.reportNonFatalError("NativeSaver, save: "+nativeSaver.name, e.getCause());
            }
        }
    }
    public static void readCallback(long player, long tag){
        NativeCompoundTag _tag = new NativeCompoundTag(tag);
        _tag.setFinalizable(false);
        Object[] args = {player, null};
        for (NativeSaver nativeSaver : savers){
            try {
                args[1] = getSaverTag(nativeSaver.name, _tag);
                if(nativeSaver.read != null)
                    JsHelper.callFunction(nativeSaver.read, args);
            } catch (Exception e) {
                DialogHelper.reportNonFatalError("NativeSaver, read: "+nativeSaver.name, e.getCause());
            }
        }
    }
}
