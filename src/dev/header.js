let BlockPos = WRAP_JAVA("com.core.api.mcpe.api.BlockPos");
let Vec2 = WRAP_JAVA("com.core.api.mcpe.api.Vec2");
let Vec3 = WRAP_JAVA("com.core.api.mcpe.api.Vec3");
let ChunkPos = WRAP_JAVA("com.core.api.mcpe.api.ChunkPos");
let Parameter = WRAP_JAVA("com.core.api.module.types.Parameter");
let Injector = WRAP_JAVA("com.core.api.Injector");
let ToolTip = WRAP_JAVA("com.core.api.item.ToolTip");

Callback.addCallback("ItemUse", function(coords, item){
    let pos = new BlockPos(coords.x, coords.y, coords.z);
    let offset = new Injector(pos).getOffset();
    alert(offset.getInt(0)+" "+offset.getInt(1)+" "+offset.getInt(2));
    pos.free();
    let ptr = ItemsUtil.getItemById(NativeAPI.staticToDynamic(item.id));
    alert(item.id+" "+ptr)
    let injector = new Injector(ptr);
    alert(injector.getIntResult("_ZNK4Item15getAttackDamageEv", [], "", true));
    injector.free();
});
ToolTip.addDynamicPre(VanillaItemID.netherite_sword, -1, function(item){
    return "data - "+item.data;
});