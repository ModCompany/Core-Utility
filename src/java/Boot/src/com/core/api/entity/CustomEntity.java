package com.core.api.entity;

import java.util.HashMap;

import com.core.api.JsHelper;
import com.zhekasmirnov.horizon.runtime.logger.Logger;
import com.zhekasmirnov.innercore.api.log.DialogHelper;
import com.zhekasmirnov.innercore.api.mod.adaptedscript.AdaptedScriptAPI.Entity;

import org.mozilla.javascript.Function;

public class CustomEntity {
    native public static void setTick(String name, boolean value);

    public static HashMap<String, Function> handlers = new HashMap<>();

    public static void setHandlerTick(String name, Function function){
        setTick(name, true);
        handlers.put(name, function);
    }

    public static void tickEntity(long ent){
        try{
            JsHelper.callFunction(handlers.get(Entity.getTypeName(ent)), new Object[] {ent});
        }catch(Exception e){
            Logger.error("Core", e.getLocalizedMessage());
            DialogHelper.reportNonFatalError("Core", e.getCause());
        }
        
    }
};