#pragma once

#include <mce.h>
#include <Core.h>
#include <type/AutomaticID.h>
#include <level/dimension/Dimension.h>
class TickingArea;
class BossbarManager;
class TickingAreasManager;
class Player;
class ItemStack;
class Actor;
class BlockPos;
class FeatureRegistry;
class BlockSource;
class Vec3;
class ActorFactory;
class Random;
class Spawner;
#include <horizon/item.h>
#include <innercore/item_registry.h>
#include <innercore/id_conversion_map.h>
class Level {
    public:
    TickingAreasManager* areas_manager;
    
    void addEntity(BlockSource&, stl::unique_ptr<Actor>);
    virtual void addGlobalEntity(BlockSource&, stl::unique_ptr<Actor>);
    void spawnEntity(BlockSource*, Vec3* pos, Actor* actor);

    public:
    TickingArea* getTickingArea(mce::UUID const&) const;
    Player* getRandomPlayer();
    Core::Random getRandom() const;
    TickingAreasManager& getTickingAreasMgr();
    Dimension& getDimension(AutomaticID<Dimension, int>) const;
    Actor* fetchEntity(ActorUniqueID, bool) const;
    FeatureRegistry& getFeatureRegistry();
    BlockPos const& getSpawnPos() const;
    ActorFactory const& getActorFactory();
    Spawner* getSpawner() const;
    ItemStack* getItemStackForId(short id,int aux){
        Item* item = ItemRegistry::getItemById(IdConversion::staticToDynamic(id,IdConversion::Scope::ITEM));
        if(item) return new ItemStack(*item,1,aux);
        return nullptr;
    }
    public:
    float getSpecialMultiplier(AutomaticID<Dimension, int>) const;
    bool isClientSide() const;
    int getCurrentServerTick() const;
    int getCurrentTick() const;
    int getChunkTickRange() const;
};

class ServerLevel : public Level {
    public:
    BossbarManager* getBossbarManager() const;
};