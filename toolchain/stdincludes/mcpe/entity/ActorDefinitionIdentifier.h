#pragma once

#include <stl/string>
#include <stl/memory>
#define stl std::__ndk1

class Actor;
class Vec2;
class ActorDefinitionIdentifier {
    public:
        ActorDefinitionIdentifier(ActorType);
        ActorDefinitionIdentifier(stl::string const&);
        stl::string& getFullName() const;
};

class ActorFactory {
    public:
    stl::unique_ptr<Actor> createEntity(stl::string const&, ActorDefinitionIdentifier const&, Actor* actor, Vec3 const&, Vec2 const&);
};