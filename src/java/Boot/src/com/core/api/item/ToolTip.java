package com.core.api.item;

public class ToolTip {
    native public static void addToolTip(int id, int data, String name);
    native public static void clearToolTips();
    native public static String[] getToolTips(int id, int data);
    native public static void clearToolTip(int id, int data);
    
    
    public static void deletToolTip(int id, int data, String name){
        String[] tips = getToolTips(id, data);
        clearToolTip(id, data);
        for(String tip : tips){
            if(tip != name)
                addToolTip(id, data, tip);
        }
    }
    public static void addToolTips(int id, int data, String[] tips){
        for(String name : tips)
            addToolTip(id, data, name);
    }
}
