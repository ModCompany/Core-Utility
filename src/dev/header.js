var ChunkPos = WRAP_JAVA("com.core.api.level.ChunkPos");
let CustomEntityJava = WRAP_JAVA("com.core.api.entity.CustomEntity");

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


Callback.addCallback("OnEnchant",function(){
    Game.message("onEnchant");
});
var debug = 0;

let GlobalContext = WRAP_JAVA("com.core.api.innnercore.GlobalContext");


let phase = 0;
let string = WRAP_JAVA("java.lang.String");
let BlockPos = WRAP_JAVA("com.core.api.engine.data.BlockPos");

var Spawner = WRAP_NATIVE("Spawner");