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
let TextElement = WRAP_JAVA("com.core.api.engine.ui.types.TextElement");
let MeshElement = WRAP_JAVA("com.core.api.engine.ui.types.MeshElement");

if(__config__.getBool("membory_display") == true){
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
                obj.font.color = android.graphics.Color.RED;
            else if(float >= .6)
                obj.font.color = android.graphics.Color.YELLOW;
            else
                obj.font.color = android.graphics.Color.GREEN;
            obj.text = free + "/" + total;
            Membory.forceRefresh();
        }
    });
}

let TestUi = new NativeUi([
    new ImageElement({
        texture: "textures/blocks/barrel_side",
        x: 100,
        y: 100,
        width: 50,
        height: 50,
        texture_width: 16,
        texture_height: 16
    }),
    new ImageElement({
        texture: "textures/blocks/barrel_side",
        x: 100,
        y: 150,
        width: 50,
        height: 50,
        texture_width: 16,
        texture_height: 16
    }),
    new TextElement({
        text: "",
        x: 50,
        y: 50,
    }),
    new MeshElement({
        x: 100,
        y: 100,
        mesh: new RenderMesh()
    })
]);
TestUi.setListener({
    update(ui, upt){
    },
    touch(ui, type, x, y, i1, b1, b2, b3){
        if(type == 0) alert("click");
        if(ui.elements[0].isTouch(x, y)){
            ui.elements[0].x = x - ui.elements[0].width / 2;
            ui.elements[0].y = y - ui.elements[0].height / 2;

            ui.forceRefresh();
            return true;
        }
        return false;
    }
});
TestUi.open();
Callback.addCallback("ItemUse", function(pos, item){
    let mesh = ItemModel.getFor(item.id, item.data).getItemRenderMesh(1, false);
    mesh.scale(60, 60, 60);
    mesh.translate(0, 0, -250);
    TestUi.elements[3].mesh = mesh;
    TestUi.elements[3].texture = ItemModel.getFor(item.id, item.data).getWorldTextureName();

    TestUi.forceRefresh();
});

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