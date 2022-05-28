package com.core.api.module;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.util.ArrayList;
import java.util.List;

import com.zhekasmirnov.apparatus.modloader.ApparatusMod;
import com.zhekasmirnov.apparatus.modloader.ApparatusModLoader;
import com.zhekasmirnov.horizon.runtime.logger.Logger;
import com.zhekasmirnov.innercore.api.runtime.Callback;

import org.json.JSONArray;
import org.json.JSONObject;;

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
                        jsons.add(new JsonData(object.getString("symbol"), object.getString("callback")));
                    }
                }
            } catch (Exception e) {
                Logger.error("TEST", e.getMessage());
            }
        }
    }

    public static void hook(long pointer, String name){
        try{
            Callback.invokeCallback(name, pointer);
        }catch(Exception e){
            Logger.error("HOOK", e.getMessage());
        }
    }
}
