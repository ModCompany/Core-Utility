let BlockPos = WRAP_JAVA("com.core.api.mcpe.api.BlockPos");
let Parameter = WRAP_JAVA("com.core.api.module.types.Parameter");

Callback.addCallback("ItemUse", function(coords, item){
    if(item.id == 280){
        //let get = new InjectorJava(GlobalContext.getClientInstance().getOptions().get());

        let injector = new InjectorJava(GlobalContext.getClientInstance().getOptions().get());
        injector.setArgsType(["bool"]).call("_ZN7Options14setHideScreensEb", [
            Parameter.getBool(true)
        ]);
        injector.free();

        //get.free();
    }else{
        let injector = new InjectorJava(GlobalContext.getClientInstance().getOptions().get());
        injector.setArgsType(["bool"]).call("_ZN7Options14setHideScreensEb", [
            Parameter.getBool(false)
        ]);
        injector.free();
    }
});