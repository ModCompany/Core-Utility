package com.core.api.module.moduleapi;

import org.json.JSONObject;
import org.mozilla.javascript.Context;
import org.mozilla.javascript.Scriptable;

import com.core.api.JsHelper;
import com.core.api.module.Hook;
import com.core.api.module.ModuleAPI;
import com.core.api.module.moduleapi.filesytem.IFileSystem;

public class ModuleFolder extends ModuleAPI {
    protected IFileSystem system;
    protected JSONObject main;

    public ModuleFolder(IFileSystem system, String main_file) {
        this.system = system;

        main = system.parseJSONObject(main_file);
        
        init(getToJson(main, "name", "Not name module"), getToJson(main, "version", 1));
    }
    
    @Override
    public void loadModule(Scriptable parent) {
        super.loadModule(parent);
        JsHelper.log("Loaded "+name);

        String loaded_file_name = getToJson(main, "code", "main.js");

        try {
            String file = system.getFile(getToJson(main, "hooks", "hooks.json"));
            if(file == null) file = "[]";
            Hook.hookJsonParse(file);
        } catch (Exception e) {
            JsHelper.log(e);
        }

        try {
            String file = system.getFile(getToJson(main, "inits", "inits.json"));
            if(file == null) file = "[]";
            Hook.initLibraryParse(file);
        } catch (Exception e) {
            JsHelper.log(e);
        }

        Context context = Context.getCurrentContext();
        try{
            context.compileString(system.getFile(loaded_file_name), loaded_file_name, 1, null).exec(context, parent);
        }catch(Exception e){
            JsHelper.error(e);
        }
    }

    public IFileSystem getFileSystem() {
        return system;
    }
}
