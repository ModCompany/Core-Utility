let ItemsUtilJava = WRAP_JAVA("com.core.api.module.ItemsUtil");
let ItemsUtil = {
    api: WRAP_JAVA("com.core.api.mcpe.item.Item"),
    getItemById(id){
        return ItemsUtilJava.getItem(id);
    },
    overrideName:function(id,data, name){
        this.api.overrideName(id,data,name);
    },
    overrideArmorValue:function(id, value){
        this.api.overrideArmorValue(id, value);
    }
};