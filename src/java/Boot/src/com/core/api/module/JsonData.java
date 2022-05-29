package com.core.api.module;

public class JsonData {
    String symbol, callback, priority, returnType;
    public JsonData(String symbol, String callback, String priority, String returnType){
        this.symbol = symbol;
        this.callback = callback;
        this.priority = priority;
        this.returnType = returnType;
    }

    public String getCallback() {
        return callback;
    }

    public String getSymbol() {
        return symbol;
    }

    public String getPriority(){
        return priority;
    }

    public String getReturn(){
        return returnType;
    }

    @Override
    public String toString() {
        return "{\"symbol\":"+symbol+",\"callback\""+callback +"}";
    }
}
