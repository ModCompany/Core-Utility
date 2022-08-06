#include <horizon/types.h>
#include <java.h>
#include <innercore_callbacks.h>

export(jlong, mcpe_api_Vec3_newClass, jfloat x, jfloat y, jfloat z){
    return (jlong) new Vec3((float) x, (float) y, (float) z);
}
export(void, mcpe_api_Vec3_setX, jlong ptr, jfloat x){
    ((Vec3*) ptr)->x = (float) x;
}
export(void, mcpe_api_Vec3_setY, jlong ptr, jfloat x){
    ((Vec3*) ptr)->y = (float) x;
}
export(void, mcpe_api_Vec3_setZ, jlong ptr, jfloat x){
    ((Vec3*) ptr)->z = (float) x;
}
export(jfloat, mcpe_api_Vec3_getX, jlong ptr){
    return (jfloat) ((Vec3*) ptr)->x;
}
export(jfloat, mcpe_api_Vec3_getY, jlong ptr){
    return (jfloat) ((Vec3*) ptr)->y;
}
export(jfloat, mcpe_api_Vec3_getZ, jlong ptr){
    return (jfloat) ((Vec3*) ptr)->z;
}
export(void, mcpe_api_Vec3_free, jlong ptr){
    ((Vec3*) ptr)->~Vec3();
}