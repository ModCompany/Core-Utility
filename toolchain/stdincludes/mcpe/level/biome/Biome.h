#pragma once

#include <stl/string.h>
#define stl std::__ndk1

class BiomeHeight;

class Biome {
    public:
    void setColor(int);
    void setName(stl::string const&);
    void setMapWaterColor(int);
    void setDepthAndScale(BiomeHeight const&);
};

