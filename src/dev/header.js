let BlockPos = WRAP_JAVA("com.core.api.mcpe.api.BlockPos");
Callback.addCallback("ItemUse", function(pos){
    let coords = new BlockPos(pos.x, pos.y, pos.z);
    coords.setY(coords.getY()+1);
    alert(pos.y + " "+ coords.getY());
    coords.free();
});
Callback.addCallback("RenderBlock", function(controller, self, render, block, pos){
    Logger.Log(pos.getX()+" "+pos.getY()+" "+pos.getZ(), "CORE");
});
