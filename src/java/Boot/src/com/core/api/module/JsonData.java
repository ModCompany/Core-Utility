package com.core.api.module;

public class JsonData {
    String symbol, callback;
    public JsonData(String symbol, String callback){
        this.symbol = symbol;
        this.callback = callback;
    }

    public String getCallback() {
        return callback;
    }

    public String getSymbol() {
        return symbol;
    }

    @Override
    public String toString() {
        return "{\"symbol\":"+symbol+",\"callback\""+callback +"}";
    }
}
