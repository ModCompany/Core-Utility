let BlockPos = WRAP_JAVA("com.core.api.mcpe.api.BlockPos");
let Vec2 = WRAP_JAVA("com.core.api.mcpe.api.Vec2");
let Vec3 = WRAP_JAVA("com.core.api.mcpe.api.Vec3");
let ChunkPos = WRAP_JAVA("com.core.api.mcpe.api.ChunkPos");
let Parameter = WRAP_JAVA("com.core.api.module.types.Parameter");
let Injector = WRAP_JAVA("com.core.api.Injector");

Callback.addCallback("ItemUse", function(){
    let pos = new BlockPos(1, 2, 3);
    let offset = new Injector(pos).getOffset();
    alert(offset.getInt(0)+" "+offset.getInt(1)+" "+offset.getInt(2));
    pos.free();
});