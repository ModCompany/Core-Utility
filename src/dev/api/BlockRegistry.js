var BlockRegistry = {
    api:WRAP_JAVA("com.core.api.engine.BlockRegistry"),

    registerDoorBlock:function(uid,name,texture){
        this.api.registerDoorBlock(BlockID[uid],uid,name,texture.name,texture.data | 0);
    }
}