package com.core.api;

import org.mozilla.javascript.Context;
import org.mozilla.javascript.Function;
import org.mozilla.javascript.Scriptable;

public class JsHelper {
    private static Context context = Context.enter();
    private static Scriptable scriptable = context.initStandardObjects();

    public static Object callFunction(Function function, Object[] args) {
        return function.call(context, scriptable, scriptable, args);
    }
}