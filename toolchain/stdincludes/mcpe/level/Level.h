#pragma once

#include <mce.h>
#include <Core.h>
#include <type/AutomaticID.h>

class TickingArea;
class BossbarManager;
class TickingAreasManager;
class Player;
class Dimension;
class Actor;
class BlockPos;
class FeatureRegistry;
class BlockSource;
class Vec3;
class ActorFactory;
class Random;

class Level {
    public:
    TickingAreasManager* areas_manager;
    TickingArea* getTickingArea(mce::UUID const&) const;
    Player* getRandomPlayer();
    Core::Random getRandom() const;
    TickingAreasManager& getTickingAreasMgr();
    Dimension& getDimension(AutomaticID<Dimension, int>) const;
    Actor* fetchEntity(ActorUniqueID, bool) const;
    float getSpecialMultiplier(AutomaticID<Dimension, int>) const;
    FeatureRegistry& getFeatureRegistry();
    BlockPos const& getSpawnPos() const;
    int getCurrentServerTick() const;
    int getCurrentTick() const;
    int getChunkTickRange() const;
    void addEntity(BlockSource*, stl::unique_ptr<Actor>);
    void spawnEntity(BlockSource*, Vec3* pos, Actor* actor);
    ActorFactory* getActorFactory();
    bool isClientSide() const;
};

class ServerLevel : public Level {
    public:
    BossbarManager* getBossbarManager() const;
};