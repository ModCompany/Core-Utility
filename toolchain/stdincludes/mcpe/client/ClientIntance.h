#pragma once

class MinecraftGame;
class Minecraft;
class LocalPlayer;
class Options;
class GuiData;
class Level;
class Actor;
class SoundEngine;
class LevelRenderer;
class ClientInstance {
public:
    MinecraftGame* getMinecraftGame() const;
    Minecraft* getServerData() const;
    LocalPlayer* getLocalPlayer() const;
    void setCameraEntity(Actor*);
    void setCameraTargetEntity(Actor*);
    Options* getOptions() const;
    GuiData* getGuiData() const;
    Level* getLevel();
    Level* getLocalServerLevel();
    Actor* getCameraTargetEntity() const;
    int getServerPingTime() const;
    SoundEngine* getSoundEngine() const;
    LevelRenderer* getLevelRenderer() const;
};


