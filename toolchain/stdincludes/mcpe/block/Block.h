#pragma once

#include <string>
#define stl std
#include <innercore/legacy_block_registry.h>
class BlockLegacy;

class Block {
    public:
    char filler[256];

    int& getRuntimeId() const;
};