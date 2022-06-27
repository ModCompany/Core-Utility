package com.core.api.item;

import java.util.HashMap;
import java.util.function.Consumer;
import java.util.ArrayList;

import org.mozilla.javascript.Context;
import org.mozilla.javascript.Function;
import org.mozilla.javascript.Scriptable;

import com.core.api.JsHelper;
import com.zhekasmirnov.innercore.api.NativeItemInstance;
import com.zhekasmirnov.innercore.api.commontypes.ItemInstance;
import com.zhekasmirnov.innercore.api.mod.util.ScriptableFunctionImpl;
import com.zhekasmirnov.innercore.api.runtime.Callback;

public class ToolTip {
    native public static void addToolTip(int id, int data, String name);
    native public static void clearToolTips();
    native public static String[] getToolTips(int id, int data);
    native public static void clearToolTip(int id, int data);
    native public static void setDynamicNameGeneration(int id);

    protected static HashMap<String, Function> mapsPost = new HashMap<>();
    protected static HashMap<String, Function> mapsPre = new HashMap<>();
    protected static ArrayList<Integer> ids = new ArrayList<>();

    public static void init(){
        Callback.addCallback("LevelLoaded", new ScriptableFunctionImpl() {
            @Override
            public Object call(Context arg0, Scriptable arg1, Scriptable arg2, Object[] arg3) {
                ids.forEach(new Consumer<Integer>() {
                    @Override
                    public void accept(Integer t) {
                        setDynamicNameGeneration(t.intValue());
                    }
                });
                return null;
            }
        }, -1);
    }

    public static void addDynamicPost(int id, int data, Function func){
        ids.add(id);
        mapsPost.put(id+":"+data, func);
    }
    public static void addDynamicPre(int id, int data, Function func){
        ids.add(id);
        mapsPre.put(id+":"+data, func);
    }
    
    public static String generateBuildDynamicToolTipPost(long item){
        try {
            NativeItemInstance instance = new NativeItemInstance(item);
            Function func = mapsPost.get(instance.id+":"+instance.data);
            if(func == null)
                func = mapsPost.get(instance.id+":-1");
            if(func != null)
                return (String) JsHelper.callFunction(func, new Object[]{new ItemInstance(instance)});
        } catch (Exception e) {}
        return "";
    }
    public static String generateBuildDynamicToolTipPre(long item){
        try {
            NativeItemInstance instance = new NativeItemInstance(item);
            Function func = mapsPre.get(instance.id+":"+instance.data);
            if(func == null)
                func = mapsPre.get(instance.id+":-1");
            if(func != null)
                return (String) JsHelper.callFunction(func, new Object[]{new ItemInstance(instance)});
        } catch (Exception e) {}
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
