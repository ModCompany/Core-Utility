#include <hook.h>
#include <mod.h>
#include <logger.h>
#include <symbol.h>
#include <innercore_callbacks.h>
#include <nativejs.h>
#include <vtable.h>

#include <java.h>

#include <stl/string>
#define stl std::__ndk1

#include <level/dimension/Dimension.h>
#include <level/Level.h>
#include <level/TickingAreasManager.h>
#include <innercore/global_context.h>

#include <horizon/types.h>
#include <core/JavaClass.h>

export(bool,level_area_TickingAreasManager_hasActiveAreas){
    ServerLevel* level = GlobalContext::getServerLevel();
    if(level!=nullptr){  
        return level->getTickingAreasMgr().hasActiveAreas();
    } 
    return false;
}

export(void, level_area_TickingAreasManager_addArea,int dimension,jstring name, jint x,jint y,jint z,jint range){
    release_string(name);
    ServerLevel* level = GlobalContext::getServerLevel();    
    if(level!=nullptr){
        level->getTickingAreasMgr().addArea(level->getDimension(dimension),stl::string(value), {x,y,z}, range);
    } 
}

export(void, level_area_TickingAreasManager_addAreaB,int dimension,jstring name, jint x,jint y,jint z,jint xx,jint yy,jint zz){
    release_string(name);
    ServerLevel* level = GlobalContext::getServerLevel();    
    if(level!=nullptr){
        level->getTickingAreasMgr().addArea(level->getDimension(dimension),stl::string(value), {x,y,z}, {xx,yy,zz});
    }     
}

export(void, level_area_TickingAreasManager_addEntityArea, jint dimension, jlong uid){
    ServerLevel* level = GlobalContext::getServerLevel();   
     
    if(level!=nullptr){
        Actor* entity = level->fetchEntity(uid, true);
        level->getTickingAreasMgr().addEntityArea(level->getDimension(dimension), *entity);
    }      
}
export(void, level_area_TickingAreasManager_removeAreaByName,int dimension, jstring name){
    release_string(name);
    ServerLevel* level = GlobalContext::getServerLevel();    
    if(level!=nullptr){
        level->getTickingAreasMgr().removePendingAreaByName(level->getDimension(dimension), stl::string(value));
    }     
}

export(void, level_area_TickingAreasManager_removeAreaByPosition, jint dimension, jint x,jint y,jint z){
    ServerLevel* level = GlobalContext::getServerLevel();    
    if(level!=nullptr){
        level->getTickingAreasMgr().removePendingAreaByPosition(level->getDimension(dimension), {x,y,z});
    }       
}
export(int, level_area_TickingAreasManager_countStandaloneTickingAreas){
    ServerLevel* level = GlobalContext::getServerLevel();    
    if(level!=nullptr){
        return level->getTickingAreasMgr().countStandaloneTickingAreas();
    }    
}

export(int, level_area_TickingAreasManager_countPendingAreas, jint dimension){
    ServerLevel* level = GlobalContext::getServerLevel();    
    if(level!=nullptr){
        return level->getTickingAreasMgr().countPendingAreas(level->getDimension(dimension));
    }        
}