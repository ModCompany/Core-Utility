package com.core.api;

import org.mozilla.javascript.Context;
import org.mozilla.javascript.Function;
import org.mozilla.javascript.Scriptable;

import com.core.api.module.types.Parameter;

public class JsHelper {
    public static Context context = Context.enter();
    public static Scriptable scriptable = context.initStandardObjects();
    private static Scriptable that = context.newObject(scriptable);

    public static Object callFunction(Function function, Object[] args) {
        return function.call(context, scriptable, that, args);
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
