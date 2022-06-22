#pragma once
#include <stl/string>
#include <stl/vector>
#include <stl/unordered_map>
#define stl std::__ndk1

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