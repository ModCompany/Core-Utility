var GlobalContext = {
    api:WRAP_JAVA("com.core.api.innnercore.GlobalContext"),

    getClientInstace:function(){
        return this.api.getClientInstace();
    },
    getServerLevel:function(){
        return this.api.getLevelServer();
    },
    getLevel:function(){
        return this.api.getLevel();
    },
    getLocalPlayer:function(){
        return this.api.getLocalPlayer();
    },
    getServerPlayer:function(){
        return this.api.getServerPlayer();
    },
    getDimension:function(){
        return this.api.getDimension();
    }
}
