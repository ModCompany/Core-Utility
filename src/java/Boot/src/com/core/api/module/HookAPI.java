package com.core.api.module;

import com.core.api.JsHelper;
import com.core.api.engine.NativeVar;
import com.zhekasmirnov.horizon.runtime.logger.Logger;
import com.zhekasmirnov.innercore.api.runtime.Callback;
/*
 * Новое api хуков, старое осталось для обратной совметисмости
 */

public class HookAPI {
    public static void hook(String callbackName, NativeVar[] args) {
        try {  
            Callback.invokeCallbackV(callbackName, args);
        } catch (Exception e) {
            JsHelper.error(e);
        }
    }
}
