#pragma once

#include <Core.h>

class ClientInstance;

class LevelListCache {
    public:
    void* getOrCreateLevelSummary(Core::Path const&);
    stl::string const& getBasePath() const;
    void _addToCache(Core::Path const&);
};
class MinecraftGame {
    public:
    ClientInstance* getPrimaryClientInstance();
    LevelListCache const& getLevelListCache();
};
