package com.core.api.module;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;

import com.core.api.module.types.Parameter;
import com.core.api.module.types.ReturnBool;
import com.core.api.module.types.ReturnInt;
import com.core.api.module.types.ReturnString;
import com.core.api.module.types.ReturnVoid;
import com.zhekasmirnov.apparatus.modloader.ApparatusMod;
import com.zhekasmirnov.apparatus.modloader.ApparatusModLoader;
import com.zhekasmirnov.horizon.runtime.logger.Logger;
import com.zhekasmirnov.innercore.api.runtime.Callback;

import org.json.JSONArray;
import org.json.JSONObject;

public class Hook {
    public static final String file_name = "hooks.json";
    private static ArrayList<JsonData> jsons = new ArrayList<>();
    public static JsonData[] getJsons(){
        return jsons.toArray(new JsonData[jsons.size()]);
    }
    public static void jsonLoad(){
        List<ApparatusMod> mods = ApparatusModLoader.getSingleton().getAllMods();
        for(int i = 0;i < mods.size();i++){
            ApparatusMod mod = mods.get(i);
            String path = mod.getInfo().getProperty("directory_root", String.class, null) + file_name;
            try {
                File file = new File(path);
                if(file.exists()){
                    BufferedReader reader = new BufferedReader(new FileReader(file));
                    String json = "";
                    String line;
                    while((line = reader.readLine()) != null)
                        json+=line;
                    reader.close();

                    JSONArray array = new JSONArray(json);
                    for(int j = 0;j < array.length();j++){
                        JSONObject object = array.getJSONObject(j);
                        JSONArray arr = object.getJSONArray("args");
                        String[] args = new String[arr.length()];
                        for(int v = 0;v < arr.length();v++)
                            args[v] = arr.getString(v);
                        jsons.add(new JsonData(object.getString("symbol"), object.getString("callback"), object.getString("priority"), object.getString("return"), args));
                    }
                }
            } catch (Exception e) {
                Logger.error("TEST", e.getMessage());
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

    public static void hookCallback(long controller, long pointer, String name, String returnType, Parameter[] args){
        try{
            Object[] args_callback = new Object[args.length+2];
            args_callback[0] = new Controller(controller, returnType);
            args_callback[1] = pointer;
            for(int i = 2;i < args_callback.length;i++)
                if(args[i - 2] != null)
                    args_callback[i] = ((Parameter) args[i - 2]).getValue();

            Callback.invokeCallback(name, args_callback);
        }catch(Exception e){
            Logger.error("HOOK", e.getMessage());
        }
    }
}
