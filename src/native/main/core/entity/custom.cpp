#include <core/entity/CustomEntity.h>
#include <core/entity/Entity.h>
#include <level/api/BlockSource.h>
#include <innercore/global_context.h>
#include <level/api/Vec3.h>

std::map<std::string, Entity*> CustomEntity::customs;

Actor* CustomEntity::getEntityByName(std::string name){
    
}

void CustomEntity::spawnEnity(BlockSource* region, Vec3* pos, std::string name){
    region->addEntity(pos, new EntityEmpty(*(region->getLevel())));
}