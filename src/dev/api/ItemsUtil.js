let ItemsUtilJava = WRAP_JAVA("com.core.api.module.ItemsUtil");
let ItemsUtil = {
    api: WRAP_JAVA("com.core.api.Item"),
    getItemById(id){
        return Number(ItemsUtilJava.getItemById(id));
    },
    overrideName:function(id,data, name){
        this.api.overrideName(id,data,name);
    },
    overrideArmorValue:function(id){
        this.api.overrideArmorValue(id);
    }
};