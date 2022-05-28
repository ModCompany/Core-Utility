package com.core.api;

import org.mozilla.javascript.Context;
import org.mozilla.javascript.Function;
import org.mozilla.javascript.Scriptable;

public class JsHelper {
    public static Context context = Context.enter();
    public static Scriptable scriptable = context.initStandardObjects();
    private static Scriptable that = context.newObject(scriptable);

    public static Object callFunction(Function function, Object[] args) {
        return function.call(context, scriptable, that, args);
    }
}
