#pragma once

class BlockSource;
class Dimension;
class Level;
class Random;
class ChunkSource {
    public:
    char filler[256];
    Level* getLevel() const;
    Dimension* getDimension() const;
};

class ChunkViewSource : public ChunkSource {
    public:
    char filler[256];
};
class StructureFeature {
    public:
    char filler[256];
    void postProcess(BlockSource&,Random&,int,int);
};

class VillageFeature : public StructureFeature{
    public:
    char filler[256];
    VillageFeature(unsigned int);
};
class WorldGenerator {
    public:
    char filler[256];
};

class FlatWorldGenerator 
{
public:
    WorldGenerator* generator;
    StructureFeature* village;
};

