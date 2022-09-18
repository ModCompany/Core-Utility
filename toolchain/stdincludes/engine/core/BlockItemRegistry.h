#pragma once

#include <stl/map>

#include <stl/string>
#define stl std::__ndk1

class BlockItemPool { 
    public:
    static stl::map<int, BlockLegacy*> block_pool;
    static stl::map<stl::string, Item*> item_pool;
    static void addBlockToPool(int uid, BlockLegacy* block){
        BlockItemPool::block_pool[uid] = block;
    };

    template<typename A> static A* getBlock(int id){
        return (A*) BlockItemPool::block_pool[id];
    }
};