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

#include <string>
#include <memory>

#define stl std


export(jlong,mcpe_level_Level_getRandomPointer,jlong pointer) {
    return (jlong) ((Level*) pointer)->getRandom();
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

