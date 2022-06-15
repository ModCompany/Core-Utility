#pragma once

class BlockSource;
#include <core/entity/Entity.h>
class Vec3;
class ItemStack;
class Spawner {
    public:
    Mob* spawnMob(BlockSource&,ActorDefinitionIdentifier const&,Actor*,Vec3 const&,bool,bool,bool);
    void* spawnItem(BlockSource&, ItemStack const&,Actor*,Vec3 const&,int);
};