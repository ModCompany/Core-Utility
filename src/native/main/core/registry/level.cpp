#include <hook.h>
#include <mod.h>
#include <logger.h>
#include <symbol.h>
#include <innercore_callbacks.h>
#include <nativejs.h>
#include <vtable.h>

#include <java.h>

#include <stl/string>
#define stl std::__ndk1

#include <level/dimension/Dimension.h>
#include <level/Level.h>
#include <level/feature/FeatureRegistry.h>


#include <innercore/global_context.h>
#include <horizon/types.h>
#include <core/JavaClass.h>


export(void, level_registry_FeatureRegistry_cleanupFeature){
    ServerLevel* level = GlobalContext::getServerLevel();
    level->getFeatureRegistry().cleanupFeatures();
}

export(float, level_Level_getSpecialMultiplier, jint dimensionid){
    return GlobalContext::getServerLevel()->getSpecialMultiplier(dimensionid);
}

export(int, level_Level_getCurrentServerTick){
    return GlobalContext::getServerLevel()->getCurrentServerTick();
}

export(int, level_Level_getCurrentTick){
    return GlobalContext::getServerLevel()->getCurrentTick();
}

export(int, level_Level_getChunkTickRange){
    return GlobalContext::getServerLevel()->getChunkTickRange();
}

