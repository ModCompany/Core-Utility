package com.core.api.engine;

import java.util.HashMap;

import org.mozilla.javascript.Context;
import org.mozilla.javascript.Function;
import org.mozilla.javascript.NativeJavaClass;
import org.mozilla.javascript.NativeJavaObject;
import org.mozilla.javascript.Scriptable;

import com.zhekasmirnov.innercore.api.mod.util.ScriptableFunctionImpl;

public class CustomWarp extends NativeJavaClass {
    public static class JsObject extends NativeJavaObject {
        NativeJavaObject thas;
        HashMap<String, Function> funcs = new HashMap<>();

        public JsObject(NativeJavaObject thas){
            this.thas = thas;
        }

        @Override
        public Object get(String name, Scriptable arg1) {
            if(name == "addMethot"){
                return new ScriptableFunctionImpl() {
                    @Override
                    public Object call(Context arg0, Scriptable arg1, Scriptable arg2, Object[] arg3) {
                        addMethot((String) arg3[0], (Function) arg3[1]);
                        return null;
                    }
                    
                };
            }
            if(funcs.containsKey(name))
                return funcs.get(name);
            return thas.get(name, arg1);
        }

        
        public void addMethot(String name, Function func){
            funcs.put(name, func);
        }

        @Override
        public void delete(String arg0) {
            thas.delete(arg0);
        }
        @Override
        public void delete(int arg0) {
            thas.delete(arg0);
        }

        @Override
        public Object get(int arg0, Scriptable arg1) {
            return thas.get(arg0, arg1);
        }

        @Override
        public String getClassName() {
            return thas.getClassName();
        }

        @Override
        public Object getDefaultValue(Class<?> arg0) {
            return thas.getDefaultValue(arg0);
        }

        @Override
        public Object[] getIds() {
            Object[] ids = thas.getIds();
            Object[] result = new Object[ids.length+1];
            for (int i = 0; i < ids.length; i++) {
                result[i] = ids[i];
            }
            result[ids.length-1] = "addMethot";
            return result;
        }

        @Override
        public Scriptable getParentScope() {
            return thas.getParentScope();
        }

        @Override
        public Scriptable getPrototype() {
            return thas.getPrototype();
        }

        @Override
        public boolean has(String arg0, Scriptable arg1) {
            if(arg0 == "addMethot") return true;
            if(funcs.containsKey(arg0)) return true;
            return thas.has(arg0, arg1);
        }

        @Override
        public boolean has(int arg0, Scriptable arg1) {
            return thas.has(arg0, arg1);
        }

        @Override
        public boolean hasInstance(Scriptable arg0) {
            return thas.hasInstance(arg0);
        }

        @Override
        public void put(String arg0, Scriptable arg1, Object arg2) {
            addMethot(arg0, (Function) arg2);
        }

        @Override
        public void put(int arg0, Scriptable arg1, Object arg2) {
            thas.put(arg0, arg1, arg2);
        }

        @Override
        public void setParentScope(Scriptable arg0) {
            thas.setParentScope(arg0);
        }

        @Override
        public void setPrototype(Scriptable arg0) {
            thas.setPrototype(arg0);
        }
    }
    public static CustomWarp init() {
        return new CustomWarp();
    }
    @Override
    public Scriptable construct(Context context, Scriptable parent, Object[] args) {
        try {
            return new JsObject(new NativeJavaClass(parent, Class.forName((String) args[0]), false));
        } catch (Exception e) {
            return super.construct(context, parent, args);
        }
    }
}
