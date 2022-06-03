#pragma once

#include <../mcpe/type/AutomaticID.h>
class BlockSource;
class TickingAreasManager;
class Dimension;
using DimensionId = AutomaticID<Dimension, int>; 

class Level;
class BlockPos;

class Weather {
    public:
    void tryToPlaceTopSnow(BlockSource&,BlockPos const&, bool, bool);
};

class Dimension {
    public:
    TickingAreasManager const& getTickingAreas();
    TickingAreasManager* getTickingAreas() const;
    DimensionId getDimensionId() const;
    Weather* getWeather() const;
    
    int getHeightRange() const;
    int getMinHeight() const;
    int getTickingAreasConst() const;
    int getMoonBrightness() const;
    bool isDay() const;
    void init() const;
    bool hasGround() const;
    Level* getLevel() const;

    public:

   // void updateBlockLight(BlockPos const&,Brightness,Brightness,Brightness,Brightness,bool);
};

class RuntimeLightManager {
    public:
    RuntimeLightManager(Dimension&);
    //void updateBlockLight(BlockPos const&,Brightness,Brightness,Brightness,Brightness,bool);

};