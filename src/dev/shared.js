ModAPI.registerAPI("CoreUtility", {
    ToolTip: ToolTip,
    ConversionType: ConversionType,
    NativeAPI: NativeAPI,
    Injector: Injector,
    CustomEntity: CustomEntity,
    requireGlobal(cmd){
        return eval(cmd);
    }
});