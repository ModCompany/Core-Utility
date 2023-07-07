let JsHelper = WRAP_JAVA("com.core.api.JsHelper");
let ModuleAPI = WRAP_JAVA("com.core.api.module.ModuleAPI");

const CoreUtility = {
    ToolTip: JsHelper.get(ToolTip),
    ConversionType: ConversionType,
    NativeAPI: NativeAPI,
    Injector: JsHelper.get(Injector),
    EntityRegister: EntityRegister,
    ItemsUtil: ItemsUtil,
    FileUtils: JsHelper.get(FileUtils),
    Gui: Gui,
    TickingAreasManager: TickingAreasManager,
    GlobalContext: GlobalContext,
    Parameter: JsHelper.get(Parameter),
    BlockPos: JsHelper.get(BlockPos),
    Vec3: JsHelper.get(Vec3),
    Vec2: JsHelper.get(Vec2),
    ChunkPos: JsHelper.get(ChunkPos),
    ItemStack: JsHelper.get(ItemStack),
    
    Actor: JsHelper.get(Actor),
    Mob: JsHelper.get(Mob),
    NativePlayer: JsHelper.get(NativePlayer),
    LocalPlayer: JsHelper.get(LocalPlayer),
    ServerPlayer: JsHelper.get(ServerPlayer),

    NativeUi: JsHelper.get(NativeUi),
    ImageElement: JsHelper.get(ImageElement),
    TextElement: JsHelper.get(TextElement),
    MeshElement: JsHelper.get(MeshElement),

    ActorDamageCause: JsHelper.get(ActorDamageCause),

    BlockUtils: BlockUtils,
    BlockRegistry: BlockRegistry,
    Scales: Scales,
    HookManager: JsHelper.get(HookManager),
    Module: JsHelper.get(ModuleAPI),
    version: Number(com.core.api.Boot.API_VERSION),
    requireGlobal(cmd){
        return eval(cmd);
    }
};

JsHelper.log("Module count "+ModuleAPI.modules.size());

for(let key in ModuleAPI.object)
    CoreUtility[key] = ModuleAPI.object[key];

with(ModuleAPI.object){
    for(let i = 0; i < ModuleAPI.modules.size();i++){
        let api = ModuleAPI.modules.get(i).getApi();
        function EXPORT(name, value){
            CoreUtility[name] = value;
        }
        api.start();
    }
}



ModAPI.registerAPI("CoreUtility", CoreUtility);

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


