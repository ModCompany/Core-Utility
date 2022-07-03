#pragma once

#include <Core.h>

class ClientInstance;


class MinecraftGame {
    public:
    ClientInstance* getPrimaryClientInstance();
    LevelListCache const& getLevelListCache();
};
