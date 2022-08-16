#pragma once

#include <stl/string>
#define stl std::__ndk1
#include <innercore/legacy_block_registry.h>
class BlockLegacy;

class Block {
    public:
    char filler[256];

    int& getRuntimeId() const;
};