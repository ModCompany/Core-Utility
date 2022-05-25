#include <core/entity/CustomEntity.h>
#include <core/entity/Entity.h>
#include <level/api/BlockSource.h>
#include <innercore/global_context.h>
#include <level/api/Vec3.h>

#include <hook.h>
#include <symbol.h>
#include <logger.h>

std::map<std::string, Entity*> CustomEntity::customs;
std::map<std::string, bool> CustomEntity::ticks;

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

void CustomEntity::spawnEnity(BlockSource* region, Vec3* pos, std::string name){
    region->addEntity(pos, new EntityEmpty(*(region->getLevel())));
}

class ActorFactory;

void CustomEntity::init(){
    /*HookManager::addCallback(
        SYMBOL("mcpe","_ZN5Actor4tickER11BlockSource"), 
        LAMBDA((Actor* thas, BlockSource& region),{
            Logger::info("TEST", "tick");
            Logger::flush();
            Logger::info("TEST", "%s", thas->getEntityTypeVTABLE().c_str());
            Logger::flush();
	    },
    ), HookManager::CALL | HookManager::LISTENER  | HookManager::RESULT);*/

    /*HookManager::addCallback(
        SYMBOL("mcpe","_ZN12ActorFactory21registerEntityMappingERK9ActorTypebRKPFNSt6__ndk110unique_ptrI5ActorNS3_14default_deleteIS5_EEEEP20ActorDefinitionGroupRK25ActorDefinitionIdentifierEN6nonstd13optional_lite8optionalIiEE"),
        LAMBDA((ActorFactory* thas, ActorType const& type, bool v, stl::unique_ptr<Actor> (* const&)(ActorDefinitionGroup*, ActorDefinitionIdentifier const&), nonstd::optional_lite::optional<int>),{
            
	    },
    ), HookManager::CALL | HookManager::LISTENER  | HookManager::RESULT);*/
}

