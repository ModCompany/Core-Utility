let ItemsUtilJava = WRAP_JAVA("com.core.api.module.ItemsUtil");
let ItemsUtil = {
    getItemById(id){
        return Number(ItemsUtilJava.getItemById(id));
    }
};