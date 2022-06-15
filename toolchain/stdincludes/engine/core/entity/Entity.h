#pragma once

#include <entity/Entity.h>

class EntityEmpty : public Actor {
    char filler[256];
    public:
        EntityEmpty(Level& level): Actor(level){}
};


