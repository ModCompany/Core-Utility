package com.core.api.module.moduleapi.filesytem;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import com.core.api.JsHelper;
import com.zhekasmirnov.innercore.api.mod.adaptedscript.AdaptedScriptAPI.FileUtil;

public class LocalFileSystem implements IFileSystem {
    protected String directory;

    protected LocalFileSystem(){}

    public LocalFileSystem(String directory){
        this.directory = directory;
    }

    @Override
    public String getFile(String path) {
        try {
            File file = new File(directory+"/"+path);
            if(file.exists()){
                BufferedReader reader = new BufferedReader(new FileReader(file));
                String json = "";
                String line;
                while((line = reader.readLine()) != null)
                    json+=line+"\n";
                reader.close();
                return json;
            }
            return null;
        } catch (Exception e) {
            JsHelper.log("error getFile");
            JsHelper.error(e);
            return null;
        }
        
    }

    @Override
    public JSONObject parseJSONObject(String path) {
        String file = getFile(path);
        if(file == null) return null;
        file = JsHelper.comment(file);

        try {
            return new JSONObject(file);
        } catch (JSONException e) {
            JsHelper.log("error parseJSONObject");
            JsHelper.error(e);
            return null;
        }
    }

    @Override
    public JSONArray parseJSONArray(String path) {
        String file = getFile(path);
        if(file == null) return null;
        file = JsHelper.comment(file);

        try {
            return new JSONArray(file);
        } catch (JSONException e) {
            JsHelper.log("error parseJSONArray");
            JsHelper.error(e);
            return null;
        }
    }
}