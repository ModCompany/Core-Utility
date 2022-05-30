package com.core.api.module.types;

import com.core.api.module.Hook;

public class ReturnVoid extends Hook.ReturnType<Double> {
    public Double getConvert(Object value){
        return ((Double) value);
    }
}
