#pragma once

#include <Core.h>
#include <client/LevelListCache.h>
#include <client/controller/PlayScreenController.h>
class Global {
    public:

    static Core::FileSystemImpl* _system_impl;
    static PlayScreenController* _world_controller;
    static LevelListCache* _world_cache;

    static Core::FileSystemImpl* getFileSystem(){
        return _system_impl;
    };

    static PlayScreenController* getWorldsController(){
        return _world_controller;
    };

    static LevelListCache* getWorldsCache(){
        return _world_cache;
    };
};

