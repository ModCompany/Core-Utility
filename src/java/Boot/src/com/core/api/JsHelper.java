package com.core.api;

import java.io.IOException;
import java.lang.reflect.Constructor;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import java.lang.reflect.Modifier;
import java.util.HashMap;

import org.mozilla.javascript.Context;
import org.mozilla.javascript.Function;
import org.mozilla.javascript.ScriptRuntime;
import org.mozilla.javascript.Scriptable;
import org.mozilla.javascript.ScriptableObject;

import com.core.api.module.types.Parameter;
import com.zhekasmirnov.horizon.runtime.logger.Logger;
import com.zhekasmirnov.innercore.api.mod.util.ScriptableFunctionImpl;

public class JsHelper {
    public static Context context = Context.enter();
    public static Scriptable scriptable = context.initStandardObjects();
    private static Scriptable that = context.newObject(scriptable);

    public static Object callFunction(Function function, Object[] args) {
        return function.call(context, scriptable, that, args);
    }
    public static class Key {

    }
    public static Function javaToJsFunction(Object obj, Method method){
        return new ScriptableFunctionImpl(){
            @Override
            public Object call(Context arg0, Scriptable arg1, Scriptable arg2, Object[] args) {
                try {
                    return method.invoke(obj, args);
                } catch (Exception e) {Logger.error(e.getMessage());}
                return null;
            }

        };
    }
    
    public static Scriptable constructClass(Class<?> _class, Object[] args) throws InstantiationException, IllegalAccessException, IllegalArgumentException, InvocationTargetException, NoSuchMethodException, SecurityException{
        HashMap<String, Function> methods = new HashMap<>();
        Class<?>[] types = new Class[args.length];
        for (int i = 0;i < args.length;i++) 
            types[i] = args[i].getClass();
        Constructor<?> constructor = _class.getConstructor(types);
        Object self = constructor.newInstance(args);
        Method[] _methots = _class.getMethods();
        for (Method method : _methots)
            methods.put(method.getName(), javaToJsFunction(self, method));
        return new Scriptable(){
            @Override
            public String getClassName() {
                return _class.getName();
            }
            @Override
            public void delete(String arg0) {
                // TODO Auto-generated method stub
                
            }
            @Override
            public void delete(int arg0) {
                // TODO Auto-generated method stub
                
            }
            @Override
            public Object get(String key, Scriptable arg1) {
                return methods.get(key);
            }
            @Override
            public Object get(int arg0, Scriptable arg1) {
                // TODO Auto-generated method stub
                return null;
            }
            @Override
            public Object getDefaultValue(Class<?> arg0) {
                // TODO Auto-generated method stub
                return null;
            }
            @Override
            public Object[] getIds() {
                // TODO Auto-generated method stub
                return null;
            }
            @Override
            public Scriptable getParentScope() {
                // TODO Auto-generated method stub
                return null;
            }
            @Override
            public Scriptable getPrototype() {
                // TODO Auto-generated method stub
                return null;
            }
            @Override
            public boolean has(String arg0, Scriptable arg1) {
                // TODO Auto-generated method stub
                return false;
            }
            @Override
            public boolean has(int arg0, Scriptable arg1) {
                // TODO Auto-generated method stub
                return false;
            }
            @Override
            public boolean hasInstance(Scriptable arg0) {
                // TODO Auto-generated method stub
                return false;
            }
            @Override
            public void put(String arg0, Scriptable arg1, Object arg2) {
                // TODO Auto-generated method stub
                
            }
            @Override
            public void put(int arg0, Scriptable arg1, Object arg2) {
                // TODO Auto-generated method stub
                
            }
            @Override
            public void setParentScope(Scriptable arg0) {
                // TODO Auto-generated method stub
                
            }
            @Override
            public void setPrototype(Scriptable arg0) {
                // TODO Auto-generated method stub
                
            }

        };
    }
    public static Function getJs(Class<?> _class){
        _class.getConstructors();
        return new ScriptableFunctionImpl(){
            @Override
            public Scriptable construct(Context context, Scriptable self, Object[] args) {
                try {
                    return constructClass(_class, args);
                } catch (Exception e) {Logger.error(e.getMessage());}
                return null;
            }
            @Override
            public Object call(Context context, Scriptable self, Scriptable scriptable, Object[] args) {
                return null;
            }
            
        };
    }
    public static Object getJs(Object _class){
        return Context.jsToJava(_class, _class.getClass());
    }

    public static Object callUnsafe(Function f, Object...obj){
        return f.call(context,scriptable,that,obj);
    }
    public static Object callFunction(Function function, Parameter[] args) {
        Object[] args_ = new Object[args.length];
        for (int i = 0; i < args_.length; i++)
            args_[i] = args[i];
        return callFunction(function, args_);
    }
}
