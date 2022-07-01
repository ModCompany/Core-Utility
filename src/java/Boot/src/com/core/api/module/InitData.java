package com.core.api.module;

public class InitData {
    public String name, lib;
    InitData(String name, String lib){
        this.name = name;
        this.lib = lib;
    }

    public String getLib() {
        return lib;
    }

    public String getName() {
        return name;
    }
}
