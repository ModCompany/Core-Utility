#pragma once

#include <api/HashedString.h>
#include <string>
#define stl std

class BlockSource;
class BlockPos;

class ItemState {
    //ItemState(unsigned int, HashedString const&, unsigned int);
};

class BlockLegacy {
    public:
        virtual void addState(ItemState const&, unsigned int);
};

class BushBlock : public BlockLegacy {
    public:
    char filler[256];

};

class CropBlock : public BushBlock {
    public:
    char filler[256];

    CropBlock(stl::string const&, int);
    int getGrowthSpeed(BlockSource&, BlockPos const&) const;
};

class CustomCropBlock : public CropBlock {
    public:
    char filler[256];

    CustomCropBlock(stl::string const& name, int itemid) : CropBlock(name,itemid) { 

    }

};
