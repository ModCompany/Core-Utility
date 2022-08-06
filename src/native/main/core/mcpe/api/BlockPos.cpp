#include <horizon/types.h>
#include <java.h>
#include <innercore_callbacks.h>

export(jlong, mcpe_api_BlockPos_newClass, jint x, jint y, jint z){
    return (jlong) new BlockPos((int) x, (int) y, (int) z);
}
export(void, mcpe_api_BlockPos_setX, jlong ptr, jint x){
    ((BlockPos*) ptr)->x = (int) x;
}
export(void, mcpe_api_BlockPos_setY, jlong ptr, jint x){
    ((BlockPos*) ptr)->y = (int) x;
}
export(void, mcpe_api_BlockPos_setZ, jlong ptr, jint x){
    ((BlockPos*) ptr)->z = (int) x;
}
export(void, mcpe_api_BlockPos_free, jlong ptr){
    ((BlockPos*) ptr)->~BlockPos();
}