var BlockRegistry = {
    api:WRAP_JAVA("com.core.api.engine.BlockRegistry"),

    registerDoorBlock:function(uid,name,texture){

        IDRegistry.genBlockID(uid);
        this.api.registerDoorBlock(BlockID[uid],uid,name,texture.name,texture.data | 0);

        Item.registerUseFunctionForID(280,function(coords,item,block){
            let source = BlockSource.getDefaultForActor(Player.get());
            
            Game.message("" + source.getBlock(coords.relative.x,coords.relative.y,coords.relative.z).toString());
        })

       /* Item.registerUseFunction(ItemID[uid],function(coords,item,block,player){
            let source = BlockSource.getDefaultForActor(player);

            var down_door = new BlockState(BlockID[uid+":block"],0).addStates({
                open_bit:0, direction: 2, door_hinge_bit: 0, upper_block_bit: 0,color: 0,
            });
            var upper_door = new BlockState(BlockID[uid+":block"],0).addStates({
                open_bit:0, direction: 2, door_hinge_bit: 0, upper_block_bit: 1,color: 0,
            });

            source.setBlock(coords.relative.x,coords.relative.y, coords.relative.z, down_door);
            source.setBlock(coords.relative.x,coords.relative.y + 1, coords.relative.z, upper_door);         
        });*/
    }
}

Callback.addCallback("LocalTick",function(){
    Game.tipMessage("" + Math.floor(Entity.getLookVector(Player.get()).x));
})