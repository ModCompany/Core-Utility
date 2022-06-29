package com.core.api.item;

import java.util.HashMap;

import org.mozilla.javascript.Function;

import com.core.api.JsHelper;
import com.zhekasmirnov.horizon.runtime.logger.Logger;
import com.zhekasmirnov.innercore.api.NativeItemInstance;
import com.zhekasmirnov.innercore.api.commontypes.ItemInstance;
public class ToolTip {
    native public static void addToolTip(int id, int data, String name);
    native public static void clearToolTips();
    native public static String[] getToolTips(int id, int data);
    native public static void clearToolTip(int id, int data);

    protected static HashMap<String, Function> mapsPost = new HashMap<>();
    protected static HashMap<String, Function> mapsPre = new HashMap<>();


    public static void addDynamicPost(int id, int data, Function func){
        mapsPost.put(id+":"+data, func);
    }
    public static void addDynamicPre(int id, int data, Function func){
        mapsPre.put(id+":"+data, func);
    }
    
    public static String generateBuildDynamicToolTipPost(long item, int data){
        try {
            NativeItemInstance instance = new NativeItemInstance(item);
            Function func = mapsPost.get(instance.id+":"+instance.data);
            instance.data = data;
            if(func == null)
                func = mapsPost.get(instance.id+":-1");
            if(func != null)
                return (String) JsHelper.callFunction(func, new Object[]{new ItemInstance(instance)});
        } catch (Exception e) {Logger.error(e.getLocalizedMessage(), "Core");}
        return "";
    }
    public static String generateBuildDynamicToolTipPre(long item, int data){
        try {
            NativeItemInstance instance = new NativeItemInstance(item);
            Function func = mapsPre.get(instance.id+":"+instance.data);
            instance.data = data;
            if(func == null)
                func = mapsPre.get(instance.id+":-1");
            if(func != null)
                return (String) JsHelper.callFunction(func, new Object[]{new ItemInstance(instance)});
        } catch (Exception e) {Logger.error(e.getLocalizedMessage(), "Core");}
        return "";
    }
    
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
