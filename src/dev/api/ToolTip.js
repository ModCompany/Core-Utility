let ToolTipJava = WRAP_JAVA("com.core.api.item.ToolTip");
let ToolTip = {
    addToolTip(id, data, name){
        ToolTipJava.addToolTip(id, data||-1, name);
    },
    addToolTips(id, data, names){
        ToolTipJava.addToolTips(id, data||-1, names);
    },
    deletToolTip(id, data, name){
        ToolTipJava.deletToolTip(id, data||-1, name);
    },
    clearToolTip(id, data){
        ToolTipJava.deletToolTip(id, data||0);
    },
    getToolTips(id, data){
        return ToolTipJava.getToolTips(id, data||0);
    },
    clearToolTips(){
        ToolTipJava.clearToolTips();
    }
};