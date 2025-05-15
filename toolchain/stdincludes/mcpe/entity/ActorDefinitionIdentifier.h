#pragma once

#include <string>
#include <memory>
#define stl std

class Actor;
class Vec2;
class ActorDefinitionIdentifier {
    public:
    char filler[256];
    ActorDefinitionIdentifier(ActorType);
    ActorDefinitionIdentifier(stl::string const&);
    stl::string& getFullName() const;
};

class ActorFactory {
    public:
        stl::unique_ptr<Actor> createEntity(stl::string const&, ActorDefinitionIdentifier const&, Actor* actor, Vec3 const&, Vec2 const&);
        stl::unique_ptr<Actor> createSpawnedEntity(ActorDefinitionIdentifier const&, Actor* actor, Vec3 const&, Vec2 const&);
        stl::unique_ptr<Actor> createSummonedEntity(ActorDefinitionIdentifier const&, Actor* actor, Vec3 const&);
        stl::unique_ptr<Actor> createBornEntity(ActorDefinitionIdentifier const&, BlockPos const&);
};