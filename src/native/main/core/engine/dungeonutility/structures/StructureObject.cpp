#include <core/DungeonUtility.h>
#include <java.h>
#include <innercore_callbacks.h>
#include <api/BlockSource.h>

void DungeonUtility::StructureObject::addBlock(BlockData* block){
    this->blocks.push_back(block);
}

void DungeonUtility::StructureObject::set(int const x, int const y, int const z, BlockSource* region) const {
    auto it = blocks.begin();
    while (it != blocks.end()){
        (*it)->setBlock(x, y, z, region);
        it++;
    }
}

export(jlong, dungeonutility_struct_StructureObject_newStructureObject){
    return (jlong) new DungeonUtility::StructureObject();
}

export(void, dungeonutility_struct_StructureObject_addBlock, jlong pointer, jlong block){
    ((DungeonUtility::StructureObject*) pointer)->addBlock((DungeonUtility::BlockData*) block);
}

export(void, dungeonutility_struct_StructureObject_set, jlong pointer, jint x, jint y, jint z, jlong region){
    ((DungeonUtility::StructureObject*) pointer)->set((int) x, (int) y, (int) z, (BlockSource*) region);
}