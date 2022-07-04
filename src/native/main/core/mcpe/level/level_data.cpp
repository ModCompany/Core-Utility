#include <level/LevelData.h>
#include <java.h>


export(void, mcpe_Level_LevelData_setSeed,jlong pointer,jint seed){
    return ((LevelData*)pointer)->setSeed((unsigned int) seed);
}

export(jint,mcpe_Level_LevelData_getSeed,jlong pointer){
    return (jint) ((LevelData*) pointer)->getSeed();
}