let JsHelper = WRAP_JAVA("com.core.api.JsHelper");

BlockUtils.getBlockById(1).addState("test", 0, 3);
BlockUtils.getBlockById(5).addState("test", 0, 3, 2);
Callback.addCallback("ItemUse", function(coords, item, block, is, player){
    Debug.m(BlockSource.getDefaultForActor(player).getBlock(coords.x, coords.y, coords.z));
});

ModAPI.registerAPI("CoreUtility", {
    ToolTip: JsHelper.get(ToolTip, this),
    ConversionType: ConversionType,
    NativeAPI: NativeAPI,
    Injector: JsHelper.get(Injector, this),
    EntityRegister: EntityRegister,
    ItemsUtil: ItemsUtil,
    Gui: Gui,
    TickingAreasManager: TickingAreasManager,
    GlobalContext: GlobalContext,
    Parameter: JsHelper.get(Parameter, this),
    BlockPos: JsHelper.get(BlockPos, this),
    Vec3: JsHelper.get(Vec3, this),
    Vec2: JsHelper.get(Vec2, this),
    ChunkPos: JsHelper.get(ChunkPos, this),
    BlockUtils: BlockUtils,
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