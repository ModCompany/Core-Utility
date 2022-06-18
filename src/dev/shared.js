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
    BlockPos: BlockPos,
    requireGlobal(cmd){
        return eval(cmd);
    }
});



var caller = WRAP_JAVA("com.core.api.engine.JniCallable");
let item = new caller();
item.register(function(){
    alert("test");
});

InjectorJava.tests(item);