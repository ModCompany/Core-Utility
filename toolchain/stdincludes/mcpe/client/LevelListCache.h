#pragma once
#include <Core.h>

class LevelListCache {
    public:
    void* getOrCreateLevelSummary(Core::Path const&);
    Core::Path& getBasePath() const;
    void _addToCache(Core::Path const&);
};
