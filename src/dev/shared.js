let JsHelper = WRAP_JAVA("com.core.api.JsHelper");

ModAPI.registerAPI("CoreUtility", {
    ToolTip: JsHelper.get(ToolTip),
    ConversionType: ConversionType,
    NativeAPI: NativeAPI,
    Injector: JsHelper.get(Injector),
    EntityRegister: EntityRegister,
    ItemsUtil: ItemsUtil,
    FileUtils: JsHelper.get(FileUtils),
    Gui: Gui,
    TickingAreasManager: TickingAreasManager,
    GlobalContext: GlobalContext,
    Parameter: JsHelper.get(Parameter),
    BlockPos: JsHelper.get(BlockPos),
    Vec3: JsHelper.get(Vec3),
    Vec2: JsHelper.get(Vec2),
    ChunkPos: JsHelper.get(ChunkPos),
    
    Actor: JsHelper.get(Actor),
    Mob: JsHelper.get(Mob),
    NativePlayer: JsHelper.get(NativePlayer),
    LocalPlayer: JsHelper.get(LocalPlayer),
    ServerPlayer: JsHelper.get(ServerPlayer),

    NativeUi: JsHelper.get(NativeUi),
    ImageElement: JsHelper.get(ImageElement),
    TextElement: JsHelper.get(TextElement),

    ActorDamageCause: JsHelper.get(ActorDamageCause),

    BlockUtils: BlockUtils,
    BlockRegistry: BlockRegistry,
    Scales: Scales,
    version: 3,
    requireGlobal(cmd){
        return eval(cmd);
    }
});
BlockRegistry.registerDoorBlock("test_block","Test Glass Door",{name:"glass"});


