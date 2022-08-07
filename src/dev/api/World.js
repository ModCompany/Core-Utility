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

World.setFlatGenerator = function(json){
    return WorldJavaAPI.setFlatGenerator(json);
};

World.setFlatGenerator('{"biome_id":1,"block_layers":[{"block_data":0,"block_id":7,"count":1},{"block_data":0,"block_id":3,"count":2},{"block_data":0,"block_id":2,"count":1}],"encoding_version":3,"structure_options":null}')

