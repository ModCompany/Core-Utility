let JsHelper = WRAP_JAVA("com.core.api.JsHelper");

ModAPI.registerAPI("CoreUtility", {
    ToolTip: JsHelper.get(ToolTip, this),
    ConversionType: ConversionType,
    NativeAPI: NativeAPI,
    Injector: JsHelper.get(Injector, this),
    EntityRegister: EntityRegister,
    ItemsUtil: ItemsUtil,
    FileUtils: JsHelper.get(FileUtils,this),
    Gui: Gui,
    TickingAreasManager: TickingAreasManager,
    GlobalContext: GlobalContext,
    Parameter: JsHelper.get(Parameter, this),
    BlockPos: JsHelper.get(BlockPos, this),
    Vec3: JsHelper.get(Vec3, this),
    Vec2: JsHelper.get(Vec2, this),
    ChunkPos: JsHelper.get(ChunkPos, this),
    BlockUtils: BlockUtils,
    BlockRegistry: BlockRegistry,
    requireGlobal(cmd){
        return eval(cmd);
    }
});



var n = WRAP_NATIVE("PlayScreen");

var window = new UI.Window({
    location:{
        x:0,
        y:0,
        width:20,
        height:20,
    },
    elements:{
        "govno":{type:"button",bitmap:"button",scale: 20,x:0,y:0,clicker:{
            onClick:function(){
                alert("work");
                n.refresh();
            }
        }}
    },

});

var container = new UI.Container();

//container.openAs(window);


//WRAP_JAVA("com.core.api.module.NativeAPI").setWorldGenerator("{'biome_id':1,'block_layers': [{'block_name': 'minecraft:dirt',count:80}],'encoding_version':5}");
/*
let block_id = IDRegistry.genBlockID("test_block");
BlockRegistry.registerDoorBlock("test_block","Test Glass Door",{name:"glass"});

Item.registerUseFunctionForID(280, function(coords,item,block){
    var source = BlockSource.getDefaultForActor(Player.get());
    var down_door = new BlockState(BlockID["test_block"],0).addStates({
        open_bit:0, direction: 0, door_hinge_bit: 0, upper_block_bit: 0, color:0
    });
    var upper_door = new BlockState(BlockID["test_block"],0).addStates({
        open_bit:0, direction: 0, door_hinge_bit: 0, upper_block_bit: 1, color:0
     });
    source.setBlock(coords.x,coords.y + 1, coords.z, down_door);
    source.setBlock(coords.x,coords.y + 2,coords.z, upper_door);
   // Debug.m(source.getBlock(coords.x,coords.y +1,coords.z));
   // Debug.m(source.getBlock(coords.x,coords.y +2,coords.z));
})*/



