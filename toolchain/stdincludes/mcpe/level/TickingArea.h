#pragma once

#include <string.h>
#define stl std

#include <mce.h>

class BlockSource;

class TickingArea {
    public:

    void remove();
    void entityHasBeenFound() const;
    void setEntityFound();
    public:
    BlockSource& getBlockSource();
    mce::UUID getId() const;
    stl::string getName() const;
    public:
    float getMaxDistToPlayers() const;
    bool isAlwaysActive() const;
    bool isEntityOwned() const;
    bool isRemoved();

};