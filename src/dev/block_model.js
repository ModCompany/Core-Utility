let model = BlockRenderer.createModel();
model.addBox(0, 0, 0, .5, .5, .5, 1, 0);

BlockRenderer.enableCoordMapping(17, 0, new ICRender.Model(model));

model = BlockRenderer.createModel();
model.addBox(0, 0, 0, .5, .5, .5, 1, 0);
model.addBox(.5, .5, .5, 1, 1, 1, 1, 0);
model = new ICRender.Model(model);
Callback.addCallback("renderBlock", function(controller, self, tessellator, block, pos){
    let x = NativeAPI.getXBlockPos(pos), y = NativeAPI.getYBlockPos(pos), z = NativeAPI.getZBlockPos(pos);
    /*let region = BlockSource.getCurrentClientRegion();
    let state = region.getBlock(x, y, z);
    if(state.id == 17 && state.getStatesScriptable()["pillar_axis"] == 1)*/
        BlockRenderer.mapAtCoords(x, y, z, model);
});