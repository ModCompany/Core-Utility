#include <horizon/types.h>
#include <horizon/item.h>
#include <core/entity/CustomEntity.h>
#include <core/entity/Entity.h>
#include <type/ActorType.h>
#include <entity/ActorDefinitionIdentifier.h>

#include <level/Spawner.h>
#include <level/api/BlockSource.h>
#include <innercore/global_context.h>


#include <hook.h>
#include <symbol.h>
#include <logger.h>
#include <innercore_callbacks.h>
#include <type/AutomaticID.h>
#include <core/JavaClass.h>


std::map<std::string, Entity*> CustomEntity::customs;
std::map<std::string, bool> CustomEntity::ticks;
jclass CustomEntity::customEntity;

Actor* CustomEntity::getEntityByName(std::string name){
    
}

bool CustomEntity::isTick(std::string name){
    if(ticks.find(name) == ticks.end())
        return false;
    return ticks[name];
}

void CustomEntity::setTick(std::string name, bool value){
    ticks[name] = value;
}

void CustomEntity::addEntity(BlockSource* region, Vec3* pos, std::string name){
    Logger::debug("TEST", "getLevel");
    Logger::flush();
    Level* level = region->getLevel();
    Logger::debug("TEST", "getActorFactory");
    Logger::flush();
    ActorFactory factory = level->getActorFactory();
    Logger::debug("TEST", "createSummonedEntity");
    Logger::flush();
    stl::unique_ptr<Actor> entity = factory.createSummonedEntity(ActorDefinitionIdentifier(stl::string(name.c_str())),GlobalContext::getLocalPlayer(), *pos);
    Logger::debug("TEST", "addEntity");
    Logger::flush();

}

class ActorFactory;

void CustomEntity::init(){
    JNIEnv* env;
    ATTACH_JAVA(env, JNI_VERSION_1_2) {
        jclass localClass = env->FindClass("com/core/api/entity/CustomEntity");
        CustomEntity::customEntity = reinterpret_cast<jclass>(env->NewGlobalRef(localClass));
    }

    HookManager::addCallback(
        SYMBOL("mcpe","_ZN5Actor4tickER11BlockSource"), 
        LAMBDA((HookManager::CallbackController* controller, Actor* thas, BlockSource& region),{
            if(CustomEntity::isTick(std::string(thas->getActorIdentifier()->getFullName().c_str())))
                JavaCallbacks::invokeControlledCallback(CustomEntity::customEntity, "tickEntity", "(J)V", controller, 0, (jlong) thas->getUniqueID().id);
	    },
    ), HookManager::CALL | HookManager::LISTENER | HookManager::CONTROLLER | HookManager::RESULT);

    /*HookManager::addCallback(
        SYMBOL("mcpe","_ZN12ActorFactory21registerEntityMappingERK9ActorTypebRKPFNSt6__ndk110unique_ptrI5ActorNS3_14default_deleteIS5_EEEEP20ActorDefinitionGroupRK25ActorDefinitionIdentifierEN6nonstd13optional_lite8optionalIiEE"),
        LAMBDA((ActorFactory* thas, ActorType const& type, bool v, stl::unique_ptr<Actor> (* const&)(ActorDefinitionGroup*, ActorDefinitionIdentifier const&), nonstd::optional_lite::optional<int>),{
            
	    },
    ), HookManager::CALL | HookManager::LISTENER  | HookManager::RESULT);*/
}

export(void,api_entity_CustomEntity_setTick,jstring name, jboolean value) {
    CustomEntity::setTick(JavaClass::toString(env,name),(bool)(value == JNI_TRUE));
}
export(void,mcpe_level_Level_addEntityLevel,jlong pointer, jfloat x, jfloat y, jfloat z, jstring name) {
    CustomEntity::addEntity((BlockSource*) pointer, new Vec3((float) x, (float) y, (float) z), JavaClass::toString(env,name));
}

#include <nativejs.h>

#include <innercore/item_registry.h>
#include <innercore/id_conversion_map.h>
#include <innercore/block_registry.h>
void test(int x,int y,int z,int i){
    ServerLevel* level = GlobalContext::getServerLevel();
    Spawner* spawn = level->getSpawner();

    spawn->spawnMob(*GlobalContext::getRegion(),ActorDefinitionIdentifier((ActorType) i),nullptr, {x,y,z},false,true,false);
}
JS_MODULE_VERSION(Spawner,1);
JS_EXPORT(Spawner, test, "V(IIII)", (JNIEnv* env, int x,int y,int z,int i){
    test(x,y,z,i);
})
