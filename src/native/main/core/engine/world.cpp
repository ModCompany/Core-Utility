
#include <java.h>
#include <Core.h>
#include <logger.h>
#include <client/LevelListCache.h>
#include <client/controller/PlayScreenController.h>
#include <core/Global.h>
#include <core/JavaClass.h>
#include <stl/string>
#define stl std::__ndk1


export(void, mcpe_World_addWorldToCache,jstring world){
    Logger::debug("CoreUtility-World","new world added to cache");
    Logger::debug("CoreUtility-World",JavaClass::toStlString(env,world).data());
    Logger::flush();
        Global::getWorldsCache()->_addToCache(Core::Path(JavaClass::toStlString(env,world)));
}

export(void, mcpe_World_updateWorlds){
    Logger::debug("CoreUtility-World","Update Local Worlds");
    Logger::flush();
    return Global::getWorldsController()->repopulateLevels();
}

export(jint, mcpe_World_getWorldsCount){
    return Global::getWorldsController()->_getLocalWorldsCount();
}

export(jlong, mcpe_World_getLevelData,jstring maybe_uid){
    return (jlong) Global::getWorldsCache()->getLevelData(JavaClass::toStlString(env,maybe_uid));
}

export(void, mcpe_World_createLevel, jstring uid,jstring path){
    return Global::getWorldsCache()->_createAndAddToCache(JavaClass::toStlString(env,uid),Core::Path(JavaClass::toStlString(env,path)));
}

#include <type/Json_new.h>


export(void, mcpe_World_setFlatGenerator, jstring json){
    Json::Value value;
    Json::Reader reader;

    reader.parse(JavaClass::toStlString(env,json),value,false);
    Logger::debug("Json",value.toStyledString().c_str());
    Logger::flush();
}