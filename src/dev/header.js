let BlockPos = WRAP_JAVA("com.core.api.mcpe.api.BlockPos");
let Vec2 = WRAP_JAVA("com.core.api.mcpe.api.Vec2");
let Vec3 = WRAP_JAVA("com.core.api.mcpe.api.Vec3");
let ChunkPos = WRAP_JAVA("com.core.api.mcpe.api.ChunkPos");
let Parameter = WRAP_JAVA("com.core.api.module.types.Parameter");
let Injector = WRAP_JAVA("com.core.api.Injector");
let ToolTip = WRAP_JAVA("com.core.api.item.ToolTip");
let NativeSaver = WRAP_JAVA("com.core.api.engine.NativeSaver");
let FileUtils = WRAP_JAVA("com.core.api.engine.FileUtils");

let CustomWarp = WRAP_JAVA("com.core.api.engine.CustomWarp");
let Warp = CustomWarp.init();

let NativeVar = WRAP_JAVA("com.core.api.engine.NativeVar");

Callback.addCallback("ItemUse", function(){
    let value = new NativeVar(6, "int");
    alert(value.get());
    value.set(Number(value.get()) * 2);
    alert(value.get());
});

/*let BlockSource_ = BlockSource;
BlockSource = new Warp("com.zhekasmirnov.apparatus.mcpe.NativeBlockSource");
function createBlockSource(region){
    try {
        let object = new CustomWarp.JsObject(region);
        object.test = function(){
            alert("hello");
        };
        return object;
    } catch (error) {
        Logger.error(error.toString());
        return region;
    }
}
try {
    BlockSource.staticTest = function(player){
        alert("createBlockSource");
        return createBlockSource(BlockSource_.getDefaultForActor(player));
    };
} catch (error) {
    Logger.error(error.toString());
}*/