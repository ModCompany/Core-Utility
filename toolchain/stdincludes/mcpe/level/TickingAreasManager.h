#pragma once

#include <stl/string.h>
#define stl std::__ndk1
class Bounds;
class Dimension;
class BlockPos;
class Actor;
class TickingAreasManager {
    public:
    void _addArea(Dimension&, stl::string const&, Bounds const&, bool);
    void addArea(Dimension&, stl::string const&, BlockPos const&, BlockPos const&);
    void addArea(Dimension&, stl::string const&, BlockPos const&, int);
    void addEntityArea(Dimension&, Actor const&);
    void removePendingAreaByName(Dimension&, stl::string const&);
    void removePendingAreaByPosition(Dimension&, BlockPos const&);
    
    public:
    int countPendingAreas(Dimension const&) const;
    int countStandaloneTickingAreas() const;
    bool hasActiveAreas() const;

    
};