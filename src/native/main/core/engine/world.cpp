
#include <java.h>
#include <Core.h>
#include <logger.h>
#include <client/LevelListCache.h>
#include <client/controller/PlayScreenController.h>
#include <core/Global.h>
#include <core/JavaClass.h>

export(void, mcpe_World_addWorldToCache,jstring world){
    Core::Path path = Core::Path(JavaClass::toStlString(env,world));
    if(Global::getFileSystem()->directoryExists(path)){
        Global::getWorldsCache()->_addToCache(path);
        Logger::debug("CoreUtility-World","Succesful add world to cache");
        Logger::flush();
    }else{
        Logger::error("CoreUtility-World-Error","directory not exist");
        Logger::flush();
    }
}

export(void, mcpe_World_updateWorlds){
    return Global::getWorldsController()->repopulateLevels();
}

export(jint, mcpe_World_getWorldsCount){
    return Global::getWorldsController()->_getLocalWorldsCount();
}

export(jlong, mcpe_World_getLevelData,jstring maybe_uid){
    return Global::getWorldsCache()->getLevelData(JavaClass::toStlString(env,maybe_uid));
}

export(void, mcpe_World_createLevel, jstring uid,jstring path){
    return Global::getWorldsCache()->_createAndAddToCache(JavaClass::toStlString(env,uid),Core::Path(JavaClass::toStlString(env,path)));
}