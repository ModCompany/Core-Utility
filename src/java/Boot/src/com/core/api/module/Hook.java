package com.core.api.module;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

import com.core.api.JsHelper;
import com.core.api.module.types.Parameter;
import com.core.api.module.types.ReturnBool;
import com.core.api.module.types.ReturnInt;
import com.core.api.module.types.ReturnString;
import com.core.api.module.types.ReturnVoid;
import com.zhekasmirnov.apparatus.modloader.ApparatusMod;
import com.zhekasmirnov.apparatus.modloader.ApparatusModLoader;
import com.zhekasmirnov.apparatus.modloader.LegacyInnerCoreMod;
import com.zhekasmirnov.innercore.api.runtime.Callback;

import org.json.JSONArray;
import org.json.JSONObject;

public class Hook {
    public static final String file_name = "hooks.json";
    public static final String file_name2 = "inits.json";
    private static ArrayList<JsonData> jsons = new ArrayList<>();
    private static ArrayList<InitData> inits = new ArrayList<>();
    public static JsonData[] getJsons(){
        return jsons.toArray(new JsonData[jsons.size()]);
    }
    public static InitData[] getInits(){
        return inits.toArray(new InitData[inits.size()]);
    }

    public static void hookJsonParse(String file) throws Exception{
        JSONArray array = new JSONArray(file);
        for(int j = 0;j < array.length();j++){
            JSONObject object = array.getJSONObject(j);
            String[] args;
            if(!object.isNull("args")){
                JSONArray arr = object.getJSONArray("args");
                args = new String[arr.length()];
                for(int v = 0;v < arr.length();v++)
                    args[v] = arr.getString(v);
            }else
                args = new String[] {};
                            
            jsons.add(new JsonData(
                object.getString("symbol"),
                object.getString("callback"),
                !object.isNull("priority") ? object.getString("priority") : "post", 
                !object.isNull("return") ? object.getString("return") : "void", 
                args, 
                !object.isNull("lib") ? object.getString("lib") : "mcpe",
                !object.isNull("legacyListener") ? object.getBoolean("legacyListener") : true,
                !object.isNull("version") ? object.getInt("version") : 1
            ));
        }
    }
    
    private static void hookLoad(String path){
        try{    
            String file = JsHelper.readFile(path);
            if(file == null) return;
            hookJsonParse(JsHelper.comment(file));
        }catch (Exception e) {
            JsHelper.log("Error loaded hooks");
            JsHelper.log(e);
        }
    }

    public static void initLibraryParse(String file) throws Exception {
        JSONArray array = new JSONArray(file);
        for(int j = 0;j < array.length();j++){
            JSONObject object = array.getJSONObject(j);
            inits.add(new InitData(object.getString("name"), object.getString("lib")));
        }
    }

    public static void initLibrary(String path){
        try{
            String file = JsHelper.readFile(path);
            if(file == null) return;
            
            initLibraryParse(JsHelper.comment(file));
        }catch (Exception e) {
            JsHelper.log("Error loaded inits");
            JsHelper.log(e);
        }
    }
    public static void jsonLoad(){
        List<ApparatusMod> mods = ApparatusModLoader.getSingleton().getAllMods();
        for(int i = 0;i < mods.size();i++){
            ApparatusMod mod = mods.get(i);
            if(!(mod instanceof LegacyInnerCoreMod)) continue;
            LegacyInnerCoreMod legacyInnerCoreMod = (LegacyInnerCoreMod) mod;
            String path = mod.getInfo().getProperty("directory_root", String.class, null);
            
            try {
                if(legacyInnerCoreMod.getLegacyModInstance().config.getBool("enabled")){
                    JSONObject object = new JSONObject(JsHelper.readFile(path+"build.config"));
                    if(!object.isNull("CoreUtility")){
                        JSONObject CoreUtility = object.getJSONObject("CoreUtility");
                        if(!CoreUtility.isNull("hooks")){
                            JSONArray array = CoreUtility.getJSONArray("hooks");
                            for (int j = 0; j < array.length(); j++) {
                                JSONObject description = array.getJSONObject(j);
                                hookLoad(path+description.getString("path"));
                            }
                        }else{
                            hookLoad(path+file_name);
                        }
                        if(!CoreUtility.isNull("initilization")){
                            JSONArray array = CoreUtility.getJSONArray("initilization");
                            for (int j = 0; j < array.length(); j++) {
                                JSONObject description = array.getJSONObject(j);
                                initLibrary(path+description.getString("path"));
                            }
                        }else{
                            initLibrary(path+file_name2);
                        }
                        if(!CoreUtility.isNull("modules")){
                            JSONArray array = CoreUtility.getJSONArray("modules");
                            for (int j = 0; j < array.length(); j++) {
                                JSONObject description = array.getJSONObject(j);
                                ModuleAPI.loadJson(path, path+description.getString("path"));
                            }
                        }else{
                            ModuleAPI.loadJson(path, path+"modules.json");
                        }
                    }else{
                        hookLoad(path+file_name);
                        initLibrary(path+file_name2);
                        ModuleAPI.loadJson(path, path+"modules.json");
                    }
                }
            } catch (Exception e) {
                JsHelper.log("Error jsonLoad");
            }
        }
    }

    native private static void replace(long pointer);
    native private static Object getResult(long ptr);
    native private static void setResult(long ptr, Object v);
    native private static void setIsResult(long ptr, boolean is);


    public static abstract class ReturnType<T> {
        abstract public T getConvert(Object v);
    }



    private static HashMap<String, ReturnType<?>> types = new HashMap<>();

    public static void registerType(String name, ReturnType<?> type){
        types.put(name, type);
    }

    public static Object getConvert(String name, Object type){
        return types.get(name).getConvert(type);
    }

    static {
        registerType("void", new ReturnVoid());
        registerType("int", new ReturnInt());
        registerType("stl::string", new ReturnString());
        registerType("bool", new ReturnBool());
        registerType("float", new ReturnInt());
    }

    public static class Controller {
        long ptr;
        String type;
        public Controller(long ptr, String type){
            this.ptr = ptr;
            this.type = type;
        }

        public long getPointer() {
            return ptr;
        }

        public void replace(){
            Hook.replace(ptr);
        }

        public void setResult(Object result){
            setIsResult(ptr, true);
            Hook.setResult(ptr,getConvert(type,result));
        }
    }

    public static void newHookCallback(String name, String returnType, Parameter[] args){
        try{
            Object[] args_callback = new Object[args.length];
            
            for(int i = 0;i < args.length;i++)
                if(args[i] != null)
                    args_callback[i] = args[i].getValue();
            args_callback[0] = new Controller((long) args_callback[0], returnType);
            HookManager.call(name, args_callback);
        }catch(Exception e){
            HookManager.setEnabledHook(name, false);
            JsHelper.error(e);
        }
    }

    public static void hookCallback(String name, String returnType, Parameter[] args){
        try{
            Object[] args_callback = new Object[args.length];
            
            for(int i = 0;i < args.length;i++)
                if(args[i] != null)
                    args_callback[i] = args[i].getValue();
            args_callback[0] = new Controller((long) args_callback[0], returnType);
            Callback.invokeCallback(name, args_callback);
        }catch(Exception e){
            HookManager.setEnabledHook(name, false);
            JsHelper.error(e);
        }
    }
}
