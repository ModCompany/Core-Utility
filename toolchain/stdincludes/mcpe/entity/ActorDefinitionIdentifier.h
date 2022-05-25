#pragma once

#include <stl/string>
#include <stl/memory>
#define stl std::__ndk1

class Actor;
class ActorDefinitionIdentifier {
    public:
    ActorDefinitionIdentifier(ActorType);
};

class ActorFactory {
    public:
    stl::unique_ptr<Actor> createEntity(stl::string const&, ActorDefinitionIdentifier const&, Vec3 const&, Vec2 const&);
};