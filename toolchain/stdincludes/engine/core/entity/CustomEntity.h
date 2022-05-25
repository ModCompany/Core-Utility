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
        static std::map<std::string, bool> ticks;
    public:
        static bool isTick(std::string);
        static void setTick(std::string, bool);
        static Actor* getEntityByName(std::string);
        static void spawnEnity(BlockSource*, Vec3*, std::string);
        static void init();
};