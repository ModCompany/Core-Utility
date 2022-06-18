package com.core.api.engine;

import org.mozilla.javascript.Function;

public interface JniInterface {
    
    
    void register(Function func);
    void call();
}
