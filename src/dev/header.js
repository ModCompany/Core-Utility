var ChunkPos = WRAP_JAVA("com.core.api.level.ChunkPos");
let CustomEntityJava = WRAP_JAVA("com.core.api.entity.CustomEntity");

var NativeItem = {
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
    overrideName:function(id, name){
        this.api.overrideName(id,name);
    },
    overrideArmorValue:function(id){
        this.api.overrideArmorValue(id);
    }
}


/*
var Test = WRAP_NATIVE("Test");

Test.registerBow(IDRegistry.genItemID("test_bow"));
Test.registerBlock(IDRegistry.genBlockID("test_block_1"));



Item.registerUseFunctionForID(280, function(coords,item,block){

    var source = BlockSource.getDefaultForActor(Player.get());

    var down_door = new BlockState(BlockID["test_block_1"],0).addStates({
        open_bit:0, direction: 0, door_hinge_bit: 0, upper_block_bit: 0, color:0
    });
    var upper_door = new BlockState(BlockID["test_block_1"],0).addStates({
        open_bit:0, direction: 0, door_hinge_bit: 0, upper_block_bit: 1, color:0
     });
    source.setBlock(coords.x,coords.y + 1, coords.z, down_door);
    source.setBlock(coords.x,coords.y + 2,coords.z, upper_door);
   // Debug.m(source.getBlock(coords.x,coords.y +1,coords.z));
   // Debug.m(source.getBlock(coords.x,coords.y +2,coords.z));
})

Item.registerUseFunctionForID(264, function(coords,item,block){

});*/
var Test = WRAP_JAVA("com.core.api.level.registry.FeatureRegistry");

var govno = WRAP_NATIVE("Govno");
Callback.addCallback("LevelCreated",function(){
    govno.debug();
});

Callback.addCallback("OnEnchant",function(){
    Game.message("onEnchant");
});
var debug = 0;

var level = WRAP_NATIVE("Level");

let GlobalContext = WRAP_JAVA("com.core.api.innnercore.GlobalContext");
/*
Callback.addCallback("ItemUse",function(coords,item,block,external,player){
    level.spawn(coords.relative.x,coords.relative.y,coords.relative.z);
    //alert(GlobalContext.getLevelServer().getRandom().nextInt(100));
}); */

Callback.addCallback("ItemUse", function(coords){
    Game.message("Test");
    
        level.spawn(2,coords.relative.x,coords.relative.y,coords.relative.z);
    

})