#include <horizon/types.h>
#include <java.h>
#include <innercore_callbacks.h>

export(jlong, mcpe_api_Vec2_newClass, jfloat x, jfloat y){
    return (jlong) new Vec2((float) x, (float) y);
}
export(void, mcpe_api_Vec2_setX, jlong ptr, jfloat x){
    ((Vec2*) ptr)->x = (int) x;
}
export(void, mcpe_api_Vec2_setY, jlong ptr, jfloat x){
    ((Vec2*) ptr)->y = (int) x;
}
export(jfloat, mcpe_api_Vec2_getX, jlong ptr){
    return (jfloat) ((Vec2*) ptr)->x;
}
export(jfloat, mcpe_api_Vec2_getY, jlong ptr){
    return (jfloat) ((Vec2*) ptr)->y;
}
export(void, mcpe_api_Vec2_free, jlong ptr){
    delete ((Vec2*) ptr);
}