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
    
    Actor: JsHelper.get(Actor, this),
    Mob: JsHelper.get(Mob, this),
    NativePlayer: JsHelper.get(NativePlayer, this),
    LocalPlayer: JsHelper.get(LocalPlayer, this),
    ServerPlayer: JsHelper.get(ServerPlayer, this),

    Actor: JsHelper.get(ActorDamageCause, this),

    BlockUtils: BlockUtils,
    BlockRegistry: BlockRegistry,
    Scales: Scales,
    version: 2,
    requireGlobal(cmd){
        return eval(cmd);
    }
});

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


