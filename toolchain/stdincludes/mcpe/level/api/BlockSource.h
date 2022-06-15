#pragma once

#include <level/Level.h>

class Level;

struct BlockSource {
    Level* getLevel() const;

    void addEntity(Vec3* pos, Actor* actor){
        getLevel()->spawnEntity(this, pos, actor);
    }
};