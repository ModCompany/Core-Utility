#pragma once

class Level;
class EntityRegistry;


class Minecraft {
    public:
    Level* getLevel() const;
    bool isInitialized() const;
    EntityRegistry* getEntityRegistry();
};


