#pragma once
#include <Core.h>

class ResourceLocation {
    public:
        ResourceLocation(Core::Path const&);
        Core::Path& getRelativePath() const;
        Core::Path getFullPath() const;
};

enum PackType {};

class PackIdVersion {
    public:
        PackIdVersion(stl::string const&, stl::string const&, PackType);
};

class ResourceLocationPair {
    public:
        ResourceLocationPair(ResourceLocation const&, PackIdVersion const&, int);
};