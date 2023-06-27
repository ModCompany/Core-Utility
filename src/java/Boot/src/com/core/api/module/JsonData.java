package com.core.api.module;

public class JsonData {
    String symbol, callback, priority, returnType, lib;
    String[] args;
    boolean legacyListener;
    
    public JsonData(String symbol, String callback, String priority, String returnType, String[] args, String lib, boolean legacyListener, int version){
        this.symbol = symbol;
        this.callback = callback;
        this.priority = priority;
        this.returnType = returnType;
        this.args = args;
        this.lib = lib;
        this.legacyListener = legacyListener;
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

    public boolean canLegacyListener(){
        return legacyListener;
    }

    @Override
    public String toString() {
        return "{\"symbol\":"+symbol+",\"callback\""+callback +"}";
    }
}
