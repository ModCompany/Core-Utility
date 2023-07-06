package com.core.api.module.moduleapi;

import java.util.ArrayList;
import org.json.JSONArray;
import org.json.JSONObject;
import org.mozilla.javascript.Context;
import org.mozilla.javascript.NativeJavaClass;
import org.mozilla.javascript.Scriptable;
import org.mozilla.javascript.ScriptableObject;

import com.core.api.Injector;
import com.core.api.JsHelper;
import com.core.api.module.Hook;
import com.core.api.module.HookManager;
import com.core.api.module.ModuleAPI;
import com.core.api.module.moduleapi.filesytem.IFileSystem;
import com.zhekasmirnov.innercore.api.log.ICLog;
import com.zhekasmirnov.innercore.api.mod.API;
import com.zhekasmirnov.innercore.api.mod.util.ScriptableFunctionImpl;
import com.zhekasmirnov.innercore.api.runtime.other.PrintStacking;

public class ModuleFolder extends ModuleAPI {
    protected IFileSystem system;
    protected JSONObject main;

    public ModuleFolder(IFileSystem system, String main_file) {
        this.system = system;

        main = system.parseJSONObject(main_file);
        
        init(getToJson(main, "name", "Not name module"), getToJson(main, "version", 1));
    }

    public void loadedScript(String loaded_file_name, Scriptable parent){
        if(loaded_file_name == null || parent == null) return;
        
        Context context = Context.getCurrentContext();
        try{
            context.compileString(system.getFile(loaded_file_name), loaded_file_name, 1, null).exec(context, parent);
        }catch(Exception e){
            JsHelper.error(e);
        }
    }

    public static void init(){
    }

    @Override
    public void preLoad(ArrayList<ModuleAPI> modules){
        super.preLoad(modules);
        JsHelper.log("Loaded preloader "+this.getName());

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
        
        try {
            if(!main.isNull("builtin_modules")){
                JSONArray array = main.getJSONArray("modules");
                for (int i = 0; i < array.length(); i++) 
                    modules.add(ModuleAPI.createForModule(null, array.opt(i)));
            }
            
        } catch (Exception e) {
            JsHelper.log(e);
        }

        Context context = Context.getCurrentContext();
        ScriptableObject object = (ScriptableObject) context.newObject(context.initStandardObjects());

        ScriptableObject input = API.getInstanceByName("Preloader");
        Object[] keys = input.getAllIds();
        for(Object key : keys)
            object.put(key.toString(), object, input.get(key));
            
        try {
            object.defineProperty("HookManager", new NativeJavaClass(object, HookManager.class, false), ScriptableObject.DONTENUM);
            object.defineProperty("Injector", new NativeJavaClass(object, Injector.class, false), ScriptableObject.DONTENUM);
            object.put("EXPORT", object, new ScriptableFunctionImpl() {
                @Override
                public Object call(Context context, Scriptable parent, Scriptable self, Object[] args) {
                    ModuleAPI.object.put((String) args[0], ModuleAPI.object, args[1]);
                    return null;
                }
            });
            object.put("alert", object, new ScriptableFunctionImpl() {
                @Override
                public Object call(Context context, Scriptable parent, Scriptable self, Object[] args) {
                    String str = (String) args[0];
                    ICLog.d("MOD-PRINT", str);
                    PrintStacking.print(str);
                    return null;
                }
            });
        } catch (Exception e) {
            JsHelper.log(e);
        }
        this.loadedScript(getToJson(main, "preloader", null), object);
    }
    
    @Override
    public void loadModule(Scriptable parent) {
        super.loadModule(parent);
        JsHelper.log("Loaded "+name);

        this.loadedScript(getToJson(main, "code", "main.js"), parent);
    }

    public IFileSystem getFileSystem() {
        return system;
    }
}
