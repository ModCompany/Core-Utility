package com.core.api.module;

public class JsonData {
    String symbol, callback, priority, returnType, lib;
    String[] args;
    public JsonData(String symbol, String callback, String priority, String returnType, String[] args, String lib){
        this.symbol = symbol;
        this.callback = callback;
        this.priority = priority;
        this.returnType = returnType;
        this.args = args;
        this.lib = lib;
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

    public String getLib() {
        return lib;
    }

    @Override
    public String toString() {
        return "{\"symbol\":"+symbol+",\"callback\""+callback +"}";
    }
}
