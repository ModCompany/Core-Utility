ModAPI.registerAPI("CoreUtility", {
    ToolTip: ToolTip,
    requireGlobal(cmd){
        return eval(cmd);
    }
});