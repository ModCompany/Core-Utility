package com.core.api.module.types;

import com.core.api.module.Hook;

public class ReturnString extends Hook.ReturnType<String> {
    public String getConvert(Object value){
        return (String) value;
    }
}
