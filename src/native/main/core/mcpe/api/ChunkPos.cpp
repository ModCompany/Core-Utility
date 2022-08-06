#include <horizon/types.h>
#include <java.h>
#include <innercore_callbacks.h>

export(jlong, mcpe_api_ChunkPos_newClass, jint x, jint z){
    return (jlong) new ChunkPos(BlockPos((int) x, 0, (int) z));
}
export(void, mcpe_api_ChunkPos_setX, jlong ptr, jint x){
    ((ChunkPos*) ptr)->x = (int) x;
}
export(void, mcpe_api_ChunkPos_setZ, jlong ptr, jint x){
    ((ChunkPos*) ptr)->z = (int) x;
}
export(jint, mcpe_api_ChunkPos_getX, jlong ptr){
    return (jint) ((ChunkPos*) ptr)->x;
}
export(jint, mcpe_api_ChunkPos_getZ, jlong ptr){
    return (jint) ((ChunkPos*) ptr)->z;
}
export(void, mcpe_api_ChunkPos_free, jlong ptr){
    ((ChunkPos*) ptr)->~ChunkPos();
}