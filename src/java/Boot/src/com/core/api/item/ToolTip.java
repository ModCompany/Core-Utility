package com.core.api.item;

import java.util.HashMap;

import org.mozilla.javascript.Function;

import com.core.api.JsHelper;
import com.core.api.mcpe.item.ItemStack;
import com.zhekasmirnov.horizon.runtime.logger.Logger;
public class ToolTip {
    native public static void addToolTip(int id, int data, String name);
    native public static void clearToolTips();
    native public static String[] getToolTips(int id, int data);
    native public static void clearToolTip(int id, int data);
    native public static void enablePre(int id, boolean value);
    native public static void enablePost(int id, boolean value);

    protected static HashMap<String, Function> mapsPost = new HashMap<>();
    protected static HashMap<String, Function> mapsPre = new HashMap<>();


    public static void addDynamicPost(int id, int data, Function func){
        mapsPost.put(id+":"+data, func);
        enablePost(id, true);
    }
    public static void addDynamicPre(int id, int data, Function func){
        mapsPre.put(id+":"+data, func);
        enablePre(id, true);
    }
    
    public static String generateBuildDynamicToolTipPost(ItemStack item){
        try {
            Function func = mapsPost.get(item.id+":"+item.data);
            if(func == null)
                func = mapsPost.get(item.id+":-1");
            if(func != null)
                return (String) JsHelper.callFunction(func, new Object[]{item});
        } catch (Exception e) {Logger.error("Core", e.getLocalizedMessage());}
        return "";
    }
    public static String generateBuildDynamicToolTipPre(ItemStack item){
        try {
            Function func = mapsPre.get(item.id+":"+item.data);
            if(func == null)
                func = mapsPre.get(item.id+":-1");
            if(func != null)
                return (String) JsHelper.callFunction(func, new Object[]{item});
        } catch (Exception e) {Logger.error("Core", e.getLocalizedMessage());}
        return "";
    }
    
    public static void deletToolTip(int id, int data, String name){
        String[] tips = getToolTips(id, data);
        clearToolTip(id, data);
        for(String tip : tips){
            if(!tip.equals(name))
                addToolTip(id, data, tip);
        }
    }
    public static void addToolTips(int id, int data, String[] tips){
        for(String name : tips)
            addToolTip(id, data, name);
    }
}
