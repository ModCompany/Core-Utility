var NativeAPIJava = WRAP_JAVA("com.core.api.module.NativeAPI");
var ConversionType = {
    ITEM: 0,
    BLOCK: 1
};
var NativeAPI = {
    dynamicToStatic(id, type){
        return Number(NativeAPIJava.dynamicToStatic(id, type || ConversionType.ITEM));
    },
    staticToDynamic(id, type){
        return Number(NativeAPIJava.staticToDynamic(id, type || ConversionType.ITEM));
    },
    getActorID(ptr){
        return NativeAPIJava.getActorID(ptr);
    },
    getXBlockPos(ptr){
        return Number(NativeAPIJava.getXBlockPos(ptr));
    },
    getYBlockPos(ptr){
        return Number(NativeAPIJava.getYBlockPos(ptr));
    },
    getZBlockPos(ptr){
        return Number(NativeAPIJava.getZBlockPos(ptr));
    },
    getActorById(ptr){
        return NativeAPIJava.getActorById(ptr);
    }
};