package com.core.api.module;

import com.core.api.JsHelper;
import com.core.api.engine.NativeVar;
import com.zhekasmirnov.horizon.runtime.logger.Logger;
import com.zhekasmirnov.innercore.api.runtime.Callback;
/*
 * Новое api хуков, старое осталось для обратной совметисмости
 */

public class HookAPI {
    public static void hook(NativeVar[] args) {
        Logger.debug("Ponter of java "+((long) args[0].get())+"    "+args[0].get().getClass().getName());
        try {  
            Callback.invokeCallbackV("Test", args);
        } catch (Exception e) {
            JsHelper.error(e);
        }
    }
}
