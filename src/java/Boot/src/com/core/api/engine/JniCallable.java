package com.core.api.engine;

import org.mozilla.javascript.Function;

import com.core.api.JsHelper;
import com.zhekasmirnov.horizon.runtime.logger.Logger;

public class JniCallable {

    Function f;

    
    public JniCallable(){

    }
    
    public void call() {

        JsHelper.callUnsafe(f, 123);
        
    }



    public void register(Function func) {
        f = func;
    }
    
}
