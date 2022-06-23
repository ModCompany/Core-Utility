let BlockPos = WRAP_JAVA("com.core.api.mcpe.api.BlockPos");
let Parameter = WRAP_JAVA("com.core.api.module.types.Parameter");

Callback.addCallback("ItemUse", function(coords, item, block, is, player){
    if(item.id == 280){
        /*let region = BlockSource.getDefaultForActor(player).getPointer();
        let actor = new Injector(region).setArgsType(["int", "int", "int"])
        let block_actor = actor.getPointerResult("_ZN11BlockSource14getBlockEntityEiii", [
            Parameter.getInt(coords.x),
            Parameter.getInt(coords.y),
            Parameter.getInt(coords.z)
        ]);
        if(block_actor != 0){
            let tick = new Injector(block_actor).setArgsType(["ptr"]);
            for(let i = 0;i < 500;i++)
                tick.call("_ZN10BlockActor4tickER11BlockSource", [
                    Parameter.getPointer(region)
                ]);
            tick.free();
        }else
            Game.message("BlockActor nullptr")
        actor.free();*/
        let region = new Injector(BlockSource.getDefaultForActor(player).getPointer()).setArgsType(["ptr", "ptr"]);
        region.call("_ZN11BlockSource16setBlockNoUpdateERK8BlockPosRK5Block", [
            Parameter.getPointer(new BlockPos(coords.x, coords.y, coords.z)),
            Parameter.getPointer(BlockUtils.getBlockStateForIdData(5, 3))
        ]);
        region.free();
    }
});
