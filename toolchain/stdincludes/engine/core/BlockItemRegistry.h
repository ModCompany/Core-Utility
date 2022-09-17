#pragma once

#include <stl/map>

#include <stl/string>
#define stl std::__ndk1

class BlockItemPool { 
    public:
    static stl::map<stl::string, BlockLegacy*> block_pool;
    static stl::map<stl::string, Item*> item_pool;

}