ModAPI.registerAPI("CoreUtility", {
    ToolTip: ToolTip,
    ConversionType: ConversionType,
    NativeAPI: NativeAPI,
    Injector: Injector,
    EntityRegister: EntityRegister,
    ItemsUtil: ItemsUtil,
    Gui: Gui,
    TickingAreasManager: TickingAreasManager,
    requireGlobal(cmd){
        return eval(cmd);
    }
});