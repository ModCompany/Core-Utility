#pragma once

#include <string.h>
#define stl std

class BiomeHeight;

class Biome {
    public:
    void setColor(int);
    void setName(stl::string const&);
    void setMapWaterColor(int);
    void setDepthAndScale(BiomeHeight const&);
};

