#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#define stl std

class MobEffect {
    public:
    static MobEffect* mMobEffects[29];
    stl::string const& getIconName() const;
};
namespace EffectRegistry {
    MobEffect* registerCustomEffect(){
        MobEffect* effect = new MobEffect();


        return effect;
    }
};  