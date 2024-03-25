package com.core.api.module;

import java.io.File;
import java.util.ArrayList;
import java.util.List;

import org.json.JSONArray;
import org.json.JSONObject;
import org.mozilla.javascript.Context;
import org.mozilla.javascript.Scriptable;
import org.mozilla.javascript.ScriptableObject;

import com.core.api.JsHelper;
import com.core.api.Boot;
import com.core.api.module.moduleapi.ModuleFolder;
import com.core.api.module.moduleapi.filesytem.GitHubFileSystem;
import com.core.api.module.moduleapi.filesytem.LocalFileSystem;
import com.zhekasmirnov.horizon.runtime.logger.Logger;
import com.zhekasmirnov.horizon.util.FileUtils;
import com.zhekasmirnov.innercore.api.log.DialogHelper;
import com.zhekasmirnov.innercore.api.mod.util.ScriptableFunctionImpl;
import com.zhekasmirnov.innercore.utils.FileTools;

public class ModuleAPI {
    public static ArrayList<ModuleAPI> modules = new ArrayList<>();
    public static ScriptableObject object = new ScriptableObject() {
        @Override
        public String getClassName() {
            return "object";
        }
      
    };

    public static void addModule(ModuleAPI module){
        ModuleAPI _module_install = ModuleAPI.getModule(module.getName());
        if(_module_install != null){
            if(_module_install.getVersion() < module.getVersion())
                modules.set(indexOf(module.getName()), module);
            return;
        }
        modules.add(module);
    }

    public static List<String> cache_module = new ArrayList<>();
    //private

    public static ArrayList<File> getListDirs(String path){
        ArrayList<File> list = new ArrayList<>();
        File dir = new File(path);
        File[] dirs = dir.listFiles();
        if(dirs == null) return list;
        for(File file : dirs)
            if(file.isDirectory())
                list.add(file);
        return list;
    }

    public static String cache_directory = ".cache";

    public static void init(String path){
        String path_to_cache = path+cache_directory;

        new File(path_to_cache).mkdir();
        
            
        List<File> directorys = getListDirs(path_to_cache);
        for(File file : directorys)
            cache_module.add(file.getName());

        ArrayList<ModuleAPI> modules_post = new ArrayList<>();
        for(ModuleAPI module : modules)
            module.preLoad(modules_post);
        modules = modules_post;
    }

    public static void downloadFile(String path, String path_git, GitHubFileSystem git, String def) throws Exception {
        if(path_git == null) return;
        String file = git.getFile(path_git);
        if(file == null) file = def;
        FileTools.writeFileText(path+path_git, file);
    }

    public static <T>T getToJson(JSONObject object, String name, T def){
        try {
            if(object.isNull(name)) return def;
            return (T) object.get(name);
        } catch (Exception e) {
            JsHelper.log(e);
        }
        return def;
    }

    public static void loadFromGit(GitHubFileSystem fileSystem, String main, String name, String path) throws Exception {
        JSONObject main_file = fileSystem.parseJSONObject(main);
        new File(path+name).mkdir();

        downloadFile(path+name+"/", main, fileSystem, "");
        downloadFile(path+name+"/", getToJson(main_file, "preloader", null), fileSystem, "");
        downloadFile(path+name+"/", getToJson(main_file, "code", "main.js"), fileSystem, "");
        downloadFile(path+name+"/", getToJson(main_file, "hooks", null), fileSystem, "[]");
        downloadFile(path+name+"/", getToJson(main_file, "inits", null), fileSystem, "[]");
    }


    public static ModuleAPI createModuleForGit(GitHubFileSystem fileSystem, String main, String name){
        if(!Boot.cache_module)
            return new ModuleFolder(fileSystem, main);
            
        try {
            String path = Boot.dir+cache_directory+"/";
            LocalFileSystem local = new LocalFileSystem(path+name);
            if(cache_module.indexOf(name) != -1 && !GitHubFileSystem.isConnection()){
                return new ModuleFolder(local, main);
            }else if(cache_module.indexOf(name) == -1 && !GitHubFileSystem.isConnection()){
                DialogHelper.openFormattedDialog("No internet connection", "Error loaded module "+name+"\nmodules cache:"+cache_module.toString());
                while(true){}
            }

            JSONObject local_main;
            if(cache_module.indexOf(name) != -1 && GitHubFileSystem.isConnection()){
                local_main = local.parseJSONObject(main);
                JSONObject main_file = fileSystem.parseJSONObject(main);
                if(ModuleAPI.<Integer>getToJson(local_main, "version", 1) < ModuleAPI.<Integer>getToJson(main_file, "version", 1))
                    loadFromGit(fileSystem, main, name, path);
            }else{
                loadFromGit(fileSystem, main, name, path);
                local_main = local.parseJSONObject(main);
            }

            return new ModuleFolder(local, main);
        } catch (Exception e) {
            JsHelper.error(e);
            while(true){}
        }
    }

    public static ModuleAPI createForModule(String path_to_mod, Object value) throws Exception {
        if(value instanceof String)
            return (new ModuleAPI((String) value, 1));
        else if(value instanceof JSONObject){
            JSONObject object = (JSONObject) value;
            String type = object.isNull("type") ? "builtin" : object.getString("type");
            switch(type){
                case "builtin":
                    return (new ModuleAPI(object.getString("name"), 1));
                case "local":
                    return (new ModuleFolder(new LocalFileSystem(path_to_mod+object.getString("directory")), object.isNull("main") ? "main.json" : object.getString("main")));
                case "github":
                    String directory = object.getString("directory");
                    return (createModuleForGit(new GitHubFileSystem(object.getString("user"), object.getString("repository"), directory), object.isNull("main") ? "main.json" : object.getString("main"), object.isNull("name") ? directory : object.getString("name")));
                default:
                    JsHelper.log("Not type "+type);
            }
        }
        return null;
    }

    public static void loadJson(String path_to_mod, String path){
        try {
            cache_module = FileUtils.getAllRelativePaths(new File(Boot.dir+cache_directory), true);
            JSONArray array = JsHelper.loadFromPath(path);
            if(array == null) return;
            for(int i = 0;i < array.length();i++)
                addModule(createForModule(path_to_mod, array.opt(i)));
        } catch (Exception e) {
            JsHelper.log("Error loaded module");
            JsHelper.log(e);
        }
        

    } 

    public static ModuleAPI getModule(String name){
        for(ModuleAPI module : modules)
            if(module.getName().equals(name))
                return module;
        return null;
    }

    public static int indexOf(String name){
        for(int i = 0;i < modules.size();i++){
            ModuleAPI module = modules.get(i);
            if(module.getName().equals(name))
                return i;
        }

        return -1;
    }

    public static boolean canUseModule(String name){
        for(ModuleAPI module : modules)
            if(module.getName().equals(name))
                return true;
        return false;
    }

    protected String name;
    protected int version;

    protected Scriptable api;

    protected ModuleAPI(){}

    public ModuleAPI(String name, int version){
        init(name, version);
    }

    protected void init(String name, int version){
        this.name = name;

        api = new ScriptableObject(){
            @Override
            public String getClassName() {
                return "Module";
            }
        };

        ModuleAPI self = this;

        api.put("start", api, new ScriptableFunctionImpl(){
            @Override
            public Object call(Context context, Scriptable scope, Scriptable self_, Object[] args) {
                self.loadModule(scope);
                return null;
            }
        });
    }

    public String getName() {
        return name;
    }

    public int getVersion() {
        return version;
    }

    public void preLoad(ArrayList<ModuleAPI> modules){
        modules.add(this);
    }

    public void loadModule(Scriptable parent){
    }

    public Scriptable getApi(){
        return api;
    }
}
