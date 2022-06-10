let ItemsUtilJava = WRAP_JAVA("com.core.api.module.ItemsUtil");
let ItemsUtil = {
    getItemById(id){
        return Number(ItemsUtilJava.getItemById(id));
    },
    api: WRAP_JAVA("com.core.api.Item"),
    registerItem:function(uid, name, obj){

    },
    registerTool:function(uid, texture,tier){

        let id = IDRegistry.genItemID(uid);
        this.api.registerTool(id, uid,texture,tier);
        ToolAPI.registerTool(id, "wood", ["stone"], {isNative: true});

    },
    TierType: {
        "pickaxe" : 0,
        "axe" : 1,
        "sword" : 2,
        "hoe" : 3,
        "shovel" : 4,
    },
    getType:function(a){
        if(TierType[a]) return TierType[a];
    },
    overrideName:function(id,data, name){
        this.api.overrideName(id,data,name);
    },
    overrideArmorValue:function(id){
        this.api.overrideArmorValue(id);
    }
};