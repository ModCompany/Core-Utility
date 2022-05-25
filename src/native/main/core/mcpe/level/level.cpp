#include <horizon/types.h>
#include <java.h>
#include <level/Level.h>
#include <Core.h>

#include <vtable.h>
#include <entity/Entity.h>
#include <innercore/global_context.h>
#include <nativejs.h>
#include <type/ActorType.h>

#include <entity/ActorDefinitionIdentifier.h>

#include <stl/string>
#include <stl/memory>

#define stl std::__ndk1

void Level::spawnEntity(BlockSource* region, Vec3* pos, Actor* actor){
    actor->setPosVTABLE(*pos);
   // VTABLE_FIND_OFFSET(Level_addEntity, _ZTV5Level, _ZN5Level9addEntityER11BlockSourceNSt6__ndk110unique_ptrI5ActorNS2_14default_deleteIS4_EEEE);
   // VTABLE_CALL<void*>(Level_addEntity, this, &region, stl::unique_ptr<Actor>(&actor));
}

void spawn(int id,int x,int y,int z){
    Level* level = GlobalContext::getLevel();
    Logger::debug("EntityAPI", "get level");
    Player* player = GlobalContext::getLocalPlayer();
    Logger::debug("EntityAPI", "get player");

    Logger::debug("EntityAPI", "new actor");
    ActorFactory factory = level->getActorFactory();
    Logger::debug("EntityAPI", "get factory");
    stl::unique_ptr<Actor> entity = factory.createSummonedEntity(ActorDefinitionIdentifier((ActorType) 73),player, {(float) x,(float)y,(float) z});
    Logger::debug("EntityAPI", "create entity");

    level->addEntity(*player->getRegion(),std::move(entity));

    Logger::debug("EntityAPI", "add entity to level");
    Logger::flush();

}

JS_MODULE_VERSION(Level, 1);

JS_EXPORT(Level, spawn, "V(III)", (JNIEnv* env,int id,int x,int y,int z){
    spawn(id,x,y,z);
});


export(jlong,mcpe_level_Level_getRandomPointer,jlong pointer) {
    Core::Random random = ((Level*) pointer)->getRandom();
    return (jlong) &random;
}
