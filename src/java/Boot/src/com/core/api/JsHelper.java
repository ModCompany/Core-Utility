package com.core.api;

import org.mozilla.javascript.Context;
import org.mozilla.javascript.Function;
import org.mozilla.javascript.Scriptable;
import org.mozilla.javascript.NativeJavaClass;

import com.core.api.module.types.Parameter;
import com.zhekasmirnov.innercore.api.mod.util.ScriptableFunctionImpl;

public class JsHelper {
    public static Context context = Context.enter();
    public static Scriptable scriptable = context.initStandardObjects();
    private static Scriptable that = context.newObject(scriptable);

    public static Object callFunction(Function function, Object[] args) {
        return function.call(context, scriptable, that, args);
    }

    public static Function get(Class<?> _class, Scriptable self){
        NativeJavaClass nativeClass = new NativeJavaClass(self, _class, false);
        return new ScriptableFunctionImpl(){
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
