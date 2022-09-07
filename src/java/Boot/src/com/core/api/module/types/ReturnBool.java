package com.core.api.module.types;

import com.core.api.module.Hook;

public class ReturnBool extends Hook.ReturnType<Double> {
    public Double getConvert(Object value){
        return ((Boolean) value).booleanValue() ? new Double(1)  : new Double(0);
    }
}
