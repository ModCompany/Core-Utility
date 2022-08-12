package com.core.api;

import org.mozilla.javascript.Context;
import org.mozilla.javascript.Function;
import org.mozilla.javascript.Scriptable;
import org.mozilla.javascript.NativeJavaClass;

import com.core.api.module.types.Parameter;

public class JsHelper {
    public static Context context = Context.enter();
    public static Scriptable scriptable = context.initStandardObjects();
    private static Scriptable that = context.newObject(scriptable);

    public static Object callFunction(Function function, Object[] args) {
        return function.call(context, scriptable, that, args);
    }

    public static Object get(Class<?> _class){
        NativeJavaClass nativeClass = new NativeJavaClass(scriptable, _class, true);
        return new Function(){
            @Override
            public Scriptable construct(Context context, Scriptable self, Object[] args) {
                return nativeClass.construct(context, self, args);
            }
            @Override
            public Object call(Context context, Scriptable self, Scriptable scriptable, Object[] args) {
                return nativeClass.call(context, self, scriptable, args);
            }
            @Override
            public Object get(String arg0, Scriptable arg1) {
                return nativeClass.get(arg0, arg1);
            }

            @Override
            public Object get(int arg0, Scriptable arg1) {
                return nativeClass.get(arg0, arg1);
            }

            @Override
            public void put(String arg0, Scriptable arg1, Object arg2) {
                nativeClass.put(arg0, arg1, arg2);
            }

            @Override
            public void put(int arg0, Scriptable arg1, Object arg2) {
                nativeClass.put(arg0, arg1, arg2);
            }

            @Override
            public Scriptable getParentScope() {
                return nativeClass.getParentScope();
            }

            @Override
            public Scriptable getPrototype() {
                return nativeClass.getPrototype();
            }

            @Override
            public String getClassName() {
                return nativeClass.getClassName();
            }

            @Override
            public boolean has(String arg0, Scriptable arg1) {
                return nativeClass.has(arg0, arg1);
            }

            @Override
            public boolean has(int arg0, Scriptable arg1) {
                return nativeClass.has(arg0, arg1);
            }

            @Override
            public boolean hasInstance(Scriptable arg0) {
                return nativeClass.hasInstance(arg0);
            }

            @Override
            public int hashCode() {
                return nativeClass.hashCode();
            }

            @Override
            public Object[] getIds() {
                return nativeClass.getIds();
            }
            @Override
            public void delete(String arg0) {
                nativeClass.delete(arg0);
            }
            @Override
            public void delete(int arg0) {
                nativeClass.delete(arg0);
            }
            @Override
            public Object getDefaultValue(Class<?> arg0) {
                return nativeClass.getDefaultValue(arg0);
            }
            @Override
            public void setParentScope(Scriptable arg0) {
                nativeClass.setParentScope(arg0);
            }
            @Override
            public void setPrototype(Scriptable arg0) {
                nativeClass.setPrototype(arg0);;
            }

            @Override
            protected Object clone() throws CloneNotSupportedException {
                return this;
            }
        };
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
