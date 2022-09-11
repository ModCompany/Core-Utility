package com.core.api;

import java.util.HashMap;

import org.mozilla.javascript.Context;
import org.mozilla.javascript.Function;
import org.mozilla.javascript.Scriptable;

import com.core.api.dungeonutility.struct.StructurePool;
import com.core.api.module.Hook;
import com.zhekasmirnov.horizon.runtime.logger.Logger;
import com.zhekasmirnov.innercore.api.runtime.Callback;

class Boot {
    public static void boot(HashMap<?, ?> data) {
        Hook.jsonLoad();
        Logger.debug("CoreUtility", "Java Loaded");
        Callback.addCallback("LevelPreLoaded", new Function() {
            @Override
            public void delete(String arg0) {}
            @Override
            public void delete(int arg0) {}
            @Override
            public Object get(String arg0, Scriptable arg1) {return null;}
            @Override
            public Object get(int arg0, Scriptable arg1) {return null;}
            @Override
            public String getClassName() {return null;}
            @Override
            public Object getDefaultValue(Class<?> arg0) {return null;}
            @Override
            public Object[] getIds() {return null;}
            @Override
            public Scriptable getParentScope() {return null;}
            @Override
            public Scriptable getPrototype() {return null;}
            @Override
            public boolean has(String arg0, Scriptable arg1) {return false;}
            @Override
            public boolean has(int arg0, Scriptable arg1) {return false;}
            @Override
            public boolean hasInstance(Scriptable arg0) {return false;}
            @Override
            public void put(String arg0, Scriptable arg1, Object arg2) {}
            @Override
            public void put(int arg0, Scriptable arg1, Object arg2) {}
            @Override
            public void setParentScope(Scriptable arg0) {}
            @Override
            public void setPrototype(Scriptable arg0) {}
            @Override
            public Object call(Context arg0, Scriptable arg1, Scriptable arg2, Object[] arg3) {
                StructurePool.levelPreLoaded();
                return null;
            }
            @Override
            public Scriptable construct(Context arg0, Scriptable arg1, Object[] arg2) {return null;}  
        }, 0);
    }  
}
 