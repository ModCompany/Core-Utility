#pragma once

#include <Core.h>

class ClientInstance;

class FontHandle;

class MinecraftGame {
    public:
    FontHandle* a;
    FontHandle* b;
    FontHandle* c;
    FontHandle* d;

    ClientInstance* getPrimaryClientInstance();
    LevelListCache const& getLevelListCache();
};
