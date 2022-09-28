#include <core/DungeonUtility.h>
#include <java.h>
#include <innercore_callbacks.h>
#include <innercore/block_registry.h>
#include <innercore/id_conversion_map.h>
#include <api/BlockSource.h>

DungeonUtility::BlockData::BlockData(BlockPos* pos, Block* block, Block* extra): pos(pos), block(block), extra(extra){

};

void DungeonUtility::BlockData::setBlock(int const x, int const y, int const z, BlockSource* region) const {
    region->setBlock(x + pos->x, y +pos->y, z + pos->z, *block, 3);
}

export(jlong, dungeonutility_api_BlockData_getBlock, jlong pointer){
    Block* block = ((DungeonUtility::BlockData*) pointer)->block;
    //return (jlong) ((((uint64_t) id << 16) | (uint64_t) data) | ((uint64_t) block.getRuntimeId() « 32));
}

export(jlong, dungeonutility_api_BlockData_newBlockData, jint x, jint y, jint z, jlong block, jlong extra){
    return (jlong) new DungeonUtility::BlockData(new BlockPos((int) x, (int) y, (int) z), (Block*) block, (Block*) extra);
}