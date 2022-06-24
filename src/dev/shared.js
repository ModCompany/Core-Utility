let JsHelper = WRAP_JAVA("com.core.api.JsHelper");
ModAPI.registerAPI("CoreUtility", {
    ToolTip: ToolTip,
    ConversionType: ConversionType,
    NativeAPI: NativeAPI,
    Injector: Injector,
    EntityRegister: EntityRegister,
    ItemsUtil: ItemsUtil,
    Gui: Gui,
    TickingAreasManager: TickingAreasManager,
    GlobalContext: GlobalContext,
    BlockPos: JsHelper.getJs(BlockPos),
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

Callback.addCallback("ItemUse",function(){
    var a = WRAP_NATIVE("PlayScreen");
    a.refresh();
});