#include <horizon/types.h>
#include <java.h>
#include <innercore_callbacks.h>

export(jlong, mcpe_api_ChunckPos_newClass, jint x, jint z){
    return (jlong) new ChunkPos(BlockPos((int) x, 0, (int) z));
}
export(void, mcpe_api_ChunckPos_setX, jlong ptr, jint x){
    ((ChunkPos*) ptr)->x = (int) x;
}
export(void, mcpe_api_ChunckPos_setZ, jlong ptr, jint x){
    ((ChunkPos*) ptr)->z = (int) x;
}
export(jint, mcpe_api_ChunckPos_getX, jlong ptr, jint x){
    ((ChunkPos*) ptr)->x = (int) x;
}
export(jint, mcpe_api_ChunckPos_getZ, jlong ptr, jint x){
    ((ChunkPos*) ptr)->z = (int) x;
}
export(void, mcpe_api_ChunckPos_free, jlong ptr){
    delete ((ChunkPos*) ptr);
}