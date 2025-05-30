#pragma once

#include <string>
#define stl std
#include <jni.h>

class Attribute;
class ActorUniqueID;
class Vec3;
class Level;
class ActorDefinitionIdentifier;
class BlockSource;
class Actor {
    public:
    
    public:
    Actor(Level&);
    bool isOnHotBlock() const;
    bool isInWaterOrRain() const;
    bool isInLava() const;
    bool isOnFire() const;
    bool isInWater() const;
    bool isSwimming() const;
    bool isSitting() const;
    bool isInsidePortal();
    bool isShootable();
    bool isInClouds() const;
    bool isClimbing() const;
    bool isBlocking() const;
    bool isCreative() const;
    bool isImmobile() const;
    bool isSneaking() const;
	bool wasHurt();
    ActorDefinitionIdentifier* getActorIdentifier() const;
    ActorUniqueID* getUniqueID() const;
    inline long long getInnerCoreId() const {
        return *(long long*) this->getUniqueID();
    }
    BlockSource* getRegion() const;
    Vec3 getPos() const;
    void setPos(Vec3 const&);
    static Actor* wrap(jlong);
    void setPosVTABLE(Vec3&);
};

class Mob : public Actor {
    public:
    void kill();
    void setTarget(Actor*);
    void setFrictionModifier(float);
    void joinCaravan(Mob*);
    void setName(stl::string const&);
    void doHurtTarget(Actor*);
    void setFlightSpeed(float);
    public:
    bool isLookingAtAnEntity();
    bool isGliding() const;
    bool isEating() const;
    bool isSneaking() const;
    bool isSprinting() const;
    public: 
    static float const LADDER_CLIMB_SPEED;
	
};

class Player : public Mob {
    public:

    public: 
    bool isJumping() const;
    bool isSleeping() const;
    bool isUsingItem() const;
    bool isPushableByPiston() const;
    bool isHungry() const;
    bool isInRaid() const;
    bool isHurt();
    void registerTrackedBoss(ActorUniqueID);
    
    public:
    static Attribute HUNGER;
};

class LocalPlayer : public Player{
    public:
    bool hasBossRegistered(ActorUniqueID) const;
    void displayClientMessage(std::string const&);
    void chat(std::string const&);
    void setSprinting(bool);
    void addExperience(int);
    void hurtTo(int);
    public:
    bool isHeadOnCollision();
    bool isFlying();
    public:
    static Attribute BOAT_REVERSE_FORCE;
};

class ServerPlayer : public Player {
    public:

};