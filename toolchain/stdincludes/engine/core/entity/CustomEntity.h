#pragma once

#include <string>
#include <map>

class Actor;
class Vec3;
class BlockSource;

class Entity;

class CustomEntity {
    private:
        static std::map<std::string, Entity*> customs;
    public:
        static Actor* getEntityByName(std::string);
        static void spawnEnity(BlockSource*, Vec3*, std::string);
};