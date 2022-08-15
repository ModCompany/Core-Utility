#pragma once
#include <Core.h>

class ResourceLocation {
    public:
        ResourceLocation(Core::Path const&);
        Core::Path& getRelativePath() const;
        Core::Path getFullPath() const;
};