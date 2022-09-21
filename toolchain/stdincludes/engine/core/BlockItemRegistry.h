#pragma once

#include <map>

#include <stl/string>
#define stl std::__ndk1
class BlockLegacy;
class Item;

class BlockItemPool { 
    public:
    enum FLAGS {
        Block = 1,
        Item = 2,
    };
    static std::map<int, BlockLegacy*> block_pool;
    static void addBlockToPool(int uid, BlockLegacy* block){
        BlockItemPool::block_pool[uid] = block;
        Logger::debug("CoreTest","Created block");
        Logger::flush();
    };

    template<typename A> static A* getBlock(int id){
        Logger::debug("CoreTest","GetBlock");
        Logger::flush();
        return (A*) BlockItemPool::block_pool[id];
    }

    static bool check(int id,int flag){
        if(BlockItemPool::block_pool.count(id) > 0){
            Logger::debug("CoreTest","Find");
            Logger::flush();
            return true;
        }
        return false;
    }
};