let BlockUtilsJava = WRAP_JAVA("com.core.api.innnercore.BlockUtils");

BlockUtilsJava.register(5, new ICRender.Model(new BlockRenderer.Model(5, 0)));



let BlockUtils = {
    getBlockById(id){
        return BlockUtilsJava.getBlockById(id);
    },
    getBlockStateForIdData(id, data){
        return BlockUtilsJava.getBlockStateForIdData(id,data);
    }
};