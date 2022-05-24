#include <level/Level.h>
#include <level/api/Vec3.h>
#include <vtable.h>
#include <entity/Entity.h>

void Level::spawnEntity(BlockSource* region, Vec3* pos, Actor* actor){
    actor->setPosVTABLE(*pos);
    //VTABLE_FIND_OFFSET(Level_addEntity, _ZTV5Level, _ZN5Level9addEntityER11BlockSourceNSt6__ndk110unique_ptrI5ActorNS2_14default_deleteIS4_EEEE);
    //VTABLE_CALL<void*>(Level_addEntity, this, &region, stl::unique_ptr<Actor>(&actor));
}