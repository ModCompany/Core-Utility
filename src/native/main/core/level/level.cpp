
#include <horizon/types.h>
#include <java.h>
#include <level/Level.h>

#include <vtable.h>
#include <entity/Entity.h> 

void Level::spawnEntity(BlockSource* region, Vec3* pos, Actor* actor){
    actor->setPosVTABLE(*pos);
    //stl::unique_ptr<Actor> p1((Actor) *actor);
    //VTABLE_FIND_OFFSET(Level_addEntity, _ZTV5Level, _ZN5Level9addEntityER11BlockSourceNSt6__ndk110unique_ptrI5ActorNS2_14default_deleteIS4_EEEE);
    //VTABLE_CALL<void*>(Level_addEntity, this, &region, p1);
}
