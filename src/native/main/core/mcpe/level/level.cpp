#include <horizon/types.h>
#include <java.h>
#include <level/Level.h>
#include <Core.h>

#include <vtable.h>
#include <entity/Entity.h>
#include <innercore/global_context.h>
#include <nativejs.h>
#include <type/ActorType.h>
#include <level/api/BlockSource.h>

#include <entity/ActorDefinitionIdentifier.h>

#include <stl/string>
#include <stl/memory>

#define stl std::__ndk1


export(jlong,mcpe_level_Level_getRandomPointer,jlong pointer) {
    Core::Random random = ((Level*) pointer)->getRandom();
    return (jlong) &random;
}



export(float, mcpe_level_Level_getSpecialMultiplier,jlong pointer, jint dimensionid){
    return ((Level*) pointer)->getSpecialMultiplier(dimensionid);
}

export(int, mcpe_level_Level_getCurrentServerTick, jlong pointer){
    return ((Level*) pointer)->getCurrentServerTick();
}

export(int, mcpe_level_Level_getCurrentTick, jlong pointer){
    return ((Level*) pointer)->getCurrentTick();
}

export(int, mcpe_level_Level_getChunkTickRange, jlong pointer){
    return ((Level*) pointer)->getChunkTickRange();
}
#include <client/gui/GuiData.h>
#include <client/ClientIntance.h>
JS_MODULE_VERSION(GUI, 1);

JS_EXPORT(GUI, setTitle, "V()", (JNIEnv* env){
    ClientInstance* instance = GlobalContext::getMinecraftClient();
    instance->getGuiData()->setTitle("Test Client.setTitle");
    instance->getGuiData()->setSubtitle("Test Client.setSubtitile");
    instance->getGuiData()->setFilteredText("Test Client.setFilteredText");
    instance->getGuiData()->setActionBarMessage("Action bar message");
});
#include <level/render/LevelRendererPlayer.h>
#include <level/dimension/Dimension.h>
#include <level/Level.h>

JS_EXPORT(GUI, setDestroyBlock, "V(III)", (JNIEnv* env,int x,int y,int z){
    Dimension* dim = GlobalContext::getDimension();

});

JS_EXPORT(GUI, set,"V(L)",(JNIEnv* env, long long uid){
    ServerPlayer* player = GlobalContext::getServerPlayer();
    player->registerTrackedBoss(uid);
    GlobalContext::getServerLevel()->fetchEntity(uid,true);
});