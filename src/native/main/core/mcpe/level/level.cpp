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

void spawn(int x,int y,int z){
    Level* level = GlobalContext::getServerLevel();
    ActorFactory* factory = level->getActorFactory();
    //stl::unique_ptr<Actor> entity = factory->createEntity("spawned", ActorDefinitionIdentifier((ActorType) 75), {(float) x,(float)y,(float) z}, {0,0});
    

    //level->addEntity(GlobalContext::getRegion(),std::move(entity));
}

JS_MODULE_VERSION(Level, 1);

JS_EXPORT(Level, spawn, "V(III)", (JNIEnv* env,int x,int y,int z){
    spawn(x,y,z);
});

extern "C" {
	JNIEXPORT jlong JNICALL Java_com_core_api_mcpe_level_Level_getRandomPointer
	(JNIEnv* env, jclass, jlong pointer) {
        Core::Random random = ((Level*) pointer)->getRandom();
        return (jlong) &random;
	}
}