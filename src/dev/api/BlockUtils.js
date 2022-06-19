let BlockUtilsJava = WRAP_JAVA("com.core.api.innnercore.BlockUtils");

let BlockUtils = {
    getBlockById(id){
        return BlockUtilsJava.getBlockById(id);
    },
    getBlockStateForIdData(id, data){
        return BlockUtilsJava.getBlockStateForIdData(id,data);
    }
};