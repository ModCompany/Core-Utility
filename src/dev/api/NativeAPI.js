var NativeAPIJava = WRAP_JAVA("com.core.api.module.NativeAPI");
var ConversionType = {
    ITEM: 0,
    BLOCK: 1
};
var NativeAPI = {
    dynamicToStatic(id, type){
        return  Number(NativeAPIJava.dynamicToStatic(id, type));
    },
    staticToDynamic(id, type){
        return  Number(NativeAPIJava.staticToDynamic(id, type));
    }
};