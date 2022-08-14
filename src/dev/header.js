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

let Actor = WRAP_JAVA("com.core.api.mcpe.entity.Actor");
let Mob = WRAP_JAVA("com.core.api.mcpe.entity.Mob");
let NativePlayer = WRAP_JAVA("com.core.api.mcpe.entity.Player");
let LocalPlayer = WRAP_JAVA("com.core.api.mcpe.entity.LocalPlayer");
let ServerPlayer = WRAP_JAVA("com.core.api.mcpe.entity.ServerPlayer");

let NativeVar = WRAP_JAVA("com.core.api.engine.NativeVar");
let ActorDamageCause = WRAP_JAVA("com.core.api.entity.ActorDamageCause");
let NativeUi = WRAP_JAVA("com.core.api.engine.ui.NativeUi");
let ImageElement = WRAP_JAVA("com.core.api.engine.ui.types.ImageElement");

let Membory = new UI.Window({
    drawing: [
        {type: "color", color: android.graphics.Color.argb(0, 0, 0, 0)}
    ],
    elements: {
        "membory": {type: "text", x: 0, y: 0, text: "", size: 70, font: {color: android.graphics.Color.argb(1, 1, 1, 1)}}
    }
});
Membory.setAsGameOverlay(true);
Membory.setTouchable(false);
Membory.open();

let time = 1000/30;
Threading.initThread("membory-information-update", function(){
    let context = UI.getContext();
    while(true){
        java.lang.Thread.sleep(time);
        let free = Math.floor(context.getFreeMemory() / 1024 / 1024);
        let total = Math.floor(context.getTotalMemory() / 1024 / 1024);
        let float = free/total;
        let obj = Membory.content.elements["membory"];
        if(float >= .85)
            obj.font.color = android.graphics.Color.argb(1, 0, 1, 0);
        else if(float >= .6)
            obj.font.color = android.graphics.Color.argb(1, 1, 1, 0);
        else
            obj.font.color = android.graphics.Color.argb(1, 1, 0, 0);
        obj.text = free + "/" + total;
        Membory.forceRefresh();
    }
});



let TestUi = new NativeUi([
    new ImageElement("test", 100, 100, 50, 50)
]);
Callback.addCallback("ItemUse", function(){
    if(TestUi.isOpen())
        TestUi.close();
    else
        TestUi.open();
});

/*Callback.addCallback("ItemUse", function(){
    let injector = new Injector("_ZN12HashedStringC2EPKc", ["char*"], [
        Parameter.getChar("WopaArtema")
    ])
});*/

/*
Любопытной варваре нос аторвали
let BlockSource_ = BlockSource;
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