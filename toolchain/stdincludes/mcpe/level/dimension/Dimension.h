#pragma once

#include <../mcpe/type/AutomaticID.h>
class BlockSource;
class TickingAreasManager;
class Dimension;
using DimensionId = AutomaticID<Dimension, int>; 
class Level;
class Dimension {
    public:
    TickingAreasManager const& getTickingAreas();
    TickingAreasManager* getTickingAreas() const;
    DimensionId getDimensionId() const;
 
    
    int getHeightRange() const;
    int getMinHeight() const;
    int getTickingAreasConst() const;
    int getMoonBrightness() const;
    bool isDay() const;
    void init() const;
    bool hasGround() const;
    Level* getLevel() const;
};

