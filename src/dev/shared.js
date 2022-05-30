ModAPI.registerAPI("CoreUtility", {
    ToolTip: ToolTip,
    ConversionType: ConversionType,
    NativeAPI: NativeAPI,
    requireGlobal(cmd){
        return eval(cmd);
    }
});