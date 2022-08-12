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
export(jlong, mcpe_api_Vec3_lerp, jlong ptr,jlong ptr2,jlong ptr3,jfloat value){
    //Vec3.cpp:28:75: error: invalid cast from type 'Vec3' to type 'jlong {aka long long int}'
    //return (jlong) ((Vec3*) ptr)->lerpTo(*(Vec3*) ptr2,*(Vec3*) ptr3,value);
}
export(void, mcpe_api_Vec3_free, jlong ptr){
    delete ((Vec3*) ptr);
}