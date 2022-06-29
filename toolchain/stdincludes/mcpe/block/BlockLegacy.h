#pragma once

#include <api/HashedString.h>

class ItemState {
    //ItemState(unsigned int, HashedString const&, unsigned int);
};

class BlockLegacy {
    public:
        virtual void addState(ItemState const&, unsigned int);
};