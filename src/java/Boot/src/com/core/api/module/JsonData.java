package com.core.api.module;

public class JsonData {
    String symbol, callback, priority, returnType;
    String[] args;
    public JsonData(String symbol, String callback, String priority, String returnType, String[] args){
        this.symbol = symbol;
        this.callback = callback;
        this.priority = priority;
        this.returnType = returnType;
        this.args = args;
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

    public String[] getArgs(){
        return args;
    }

    @Override
    public String toString() {
        return "{\"symbol\":"+symbol+",\"callback\""+callback +"}";
    }
}
