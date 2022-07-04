#pragma once
#include <Core.h>
class LevelData;
class LevelListCache {
    public:
    void* getOrCreateLevelSummary(Core::Path const&);
    Core::Path& getBasePath() const;
    void _addToCache(Core::Path const&);
    LevelData* getLevelData(stl::string const&);
    void _createAndAddToCache(stl::string const&,Core::Path const&);
};
