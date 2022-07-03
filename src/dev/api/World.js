let WorldJavaAPI = WRAP_JAVA("com.core.api.mcpe.World");

World.addWorldToCache = function(path){
    return WorldJavaAPI.addWorldToCache(path);
};

World.updateWorlds = function(){
    return WorldJavaAPI.updateWorlds();
};

World.getWorldsCount = function(){
    return WorldJavaAPI.getWorldsCount();
};


