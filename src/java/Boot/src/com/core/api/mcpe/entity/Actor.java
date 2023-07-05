package com.core.api.mcpe.entity;

import com.core.api.Injector;
import com.core.api.engine.PointerClass;
import com.core.api.mcpe.api.Random;
import com.core.api.mcpe.api.Vec3;
import com.core.api.module.NativeAPI;
import com.core.api.module.types.Parameter;

public class Actor extends PointerClass {
    public static final String table = "_ZTV5Actor";
    Injector injector;

    public Actor(long ptr){
        super(ptr);
        injector = new Injector(ptr);
    }

    public long getId(){
        return NativeAPI.getActorID(pointer);
    }

    public boolean isBreakingObstruction(){
        return injector.setArgsType(new String[] {}).getBoolResult("_ZNK5Actor21isBreakingObstructionEv");
    }
    public boolean isPlayer(){
        return injector.setArgsType(new String[] {}).getBoolResult("_ZNK5Actor8isPlayerEv", new Object[]{}, table);
    }
    public boolean isInClouds(){
        return injector.setArgsType(new String[] {}).getBoolResult("_ZNK5Actor10isInCloudsEv");
    }
    public boolean canPowerJump(){
        return injector.setArgsType(new String[] {}).getBoolResult("_ZNK5Actor12canPowerJumpEv");
    }
    public boolean isInSnow(){
        return injector.setArgsType(new String[] {}).getBoolResult("_ZNK5Actor8isInSnowEv");
    }
    public boolean isInRain(){
        return injector.setArgsType(new String[] {}).getBoolResult("_ZNK5Actor8isInRainEv");
    }
    public boolean isInLava(){
        return injector.setArgsType(new String[] {}).getBoolResult("_ZNK5Actor8isInLavaEv", new Object[]{}, table);
    }
    public boolean isTame(){
        return injector.setArgsType(new String[] {}).getBoolResult("_ZNK5Actor6isTameEv");
    }
    public boolean isClientSide(){
        return injector.setArgsType(new String[] {}).getBoolResult("_ZNK5Actor12isClientSideEv");
    }
    public boolean isShootable(){
        return injector.setArgsType(new String[] {}).getBoolResult("_ZN5Actor11isShootableEv", new Object[]{}, table);
    }
    public boolean isBlocking(){
        return injector.setArgsType(new String[] {}).getBoolResult("_ZNK5Actor10isBlockingEv", new Object[]{}, table);
    }
    public boolean isLeashed(){
        return injector.setArgsType(new String[] {}).getBoolResult("_ZNK5Actor9isLeashedEv");
    }
    public boolean isPacified(){
        return injector.setArgsType(new String[] {}).getBoolResult("_ZNK5Actor10isPacifiedEv");
    }
    public boolean isSleeping(){
        return injector.setArgsType(new String[] {}).getBoolResult("_ZNK5Actor10isSleepingEv", new Object[]{}, table);
    }
    public boolean isTrading(){
        return injector.setArgsType(new String[] {}).getBoolResult("_ZNK5Actor9isTradingEv");
    }

    public Vec3 getPosOld(){
        return new Vec3(injector.setArgsType(new String[] {}).getPointerResult("_ZNK5Actor9getPosOldEv", new Object[]{}, table));
    }

    public Random getRandom(){
        return new Random(injector.setArgsType(new String[] {}).getPointerResult("_ZNK5Actor9getRandomEv"));
    }

    public boolean isSkyLit(float value){
        return injector.setArgsType(new String[] {"float"}).getBoolResult("_ZN5Actor8isSkyLitEf", new Object[] {
            Parameter.getFloat(value)
        }, table);
    }

    public void setDancing(boolean value){
        injector.setArgsTypes("bool").call("_ZN5Actor10setDancingEb", new Object[] {
            Parameter.getBool(value)
        });
    }
    public void setAutonomous(boolean value){
        injector.setArgsTypes("bool").call("_ZN5Actor13setAutonomousEb", new Object[] {
            Parameter.getBool(value)
        });
    }
    public void setCollidableMob(boolean value){
        injector.setArgsTypes("bool").call("_ZN5Actor16setCollidableMobEb", new Object[] {
            Parameter.getBool(value)
        });
    }
    public void setCanPowerJump(boolean value){
        injector.setArgsTypes("bool").call("_ZN5Actor15setCanPowerJumpEb", new Object[] {
            Parameter.getBool(value)
        }, table);
    }
    public void setStanding(boolean value){
        injector.setArgsTypes("bool").call("_ZN5Actor11setStandingEb", new Object[] {
            Parameter.getBool(value)
        }, table);
    }
    public void setDoorOpener(boolean value){
        injector.setArgsTypes("bool").call("_ZN5Actor13setDoorOpenerEb", new Object[] {
            Parameter.getBool(value)
        });
    }
    public void setResting(boolean value){
        injector.setArgsTypes("bool").call("_ZN5Actor10setRestingEb", new Object[] {
            Parameter.getBool(value)
        });
    }

    public void addRider(Actor value){
        injector.setArgsTypes("ptr").call("_ZN5Actor8addRiderERS_", new Object[] {
            Parameter.getPointer(value)
        }, table);
    }
    public void attack(Actor value){
        injector.setArgsTypes("ptr").call("_ZN5Actor6attackERS_", new Object[] {
            Parameter.getPointer(value)
        }, table);
    }
    public void startRiding(Actor value){
        injector.setArgsTypes("ptr").call("_ZN5Actor11startRidingERS_", new Object[] {
            Parameter.getPointer(value)
        }, table);
    }
    public boolean isRiding(Actor value){
        return injector.setArgsTypes("ptr").getBoolResult("_ZNK5Actor8isRidingEPS_", new Object[] {
            Parameter.getPointer(value)
        });
    }
    public boolean isRider(Actor value){
        return injector.setArgsTypes("ptr").getBoolResult("_ZNK5Actor7isRiderERKS_", new Object[] {
            Parameter.getPointer(value)
        });
    }
    public void setTradingPlayer(Player value){
        injector.setArgsTypes("ptr").call("_ZN5Actor16setTradingPlayerEP6Player", new Object[] {
            Parameter.getPointer(value)
        });
    }

    public void stopSwimming(){
        injector.setArgsType(new String[] {}).call("_ZN5Actor12stopSwimmingEv", new Object[] {}, table);
    }
    public void stopSpinAttack(){
        injector.setArgsType(new String[] {}).call("_ZN5Actor14stopSpinAttackEv", new Object[] {}, table);
    }

    public void breaksFallingBlocks(){
        injector.setArgsType(new String[] {}).call("_ZNK5Actor19breaksFallingBlocksEv", new Object[] {}, table);
    }

    public int getVariant(){
        return injector.setArgsType(new String[] {}).getIntResult("_ZNK5Actor10getVariantEv");
    }
    public float distanceTo(Actor actor){
        return injector.setArgsType(new String[] {"ptr"}).getFloatResult("_ZNK5Actor10distanceToERKS_", new Object[] {
            Parameter.getPointer(actor)
        });
    }
};