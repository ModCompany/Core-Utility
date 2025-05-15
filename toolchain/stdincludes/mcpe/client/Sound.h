#pragma once

#include <mod.h>
typedef struct {
  float DecayTime;
  float EarlyDelay;
  float LateDelay;
  float HFReference;
  float HFDecayRatio;
  float Diffusion;
  float Density;
  float LowShelfFrequency;
  float LowShelfGain;
  float HighCut;
  float EarlyLateMix;
  float WetLevel;
} FMOD_REVERB_PROPERTIES;

#define FMOD_PRESET_OFF {  1000,    7,  11, 5000, 100, 100, 100, 250, 0,    20,  96, -80.0f }
#define FMOD_PRESET_GENERIC {  1500,    7,  11, 5000,  83, 100, 100, 250, 0, 14500,  96,  -8.0f }
#define FMOD_PRESET_PADDEDCELL {   170,    1,   2, 5000,  10, 100, 100, 250, 0,   160,  84,  -7.8f }
#define FMOD_PRESET_ROOM {   400,    2,   3, 5000,  83, 100, 100, 250, 0,  6050,  88,  -9.4f }
#define FMOD_PRESET_BATHROOM {  1500,    7,  11, 5000,  54, 100,  60, 250, 0,  2900,  83,   0.5f }
#define FMOD_PRESET_LIVINGROOM {   500,    3,   4, 5000,  10, 100, 100, 250, 0,   160,  58, -19.0f }
#define FMOD_PRESET_STONEROOM {  2300,   12,  17, 5000,  64, 100, 100, 250, 0,  7800,  71,  -8.5f }
#define FMOD_PRESET_AUDITORIUM {  4300,   20,  30, 5000,  59, 100, 100, 250, 0,  5850,  64, -11.7f }
#define FMOD_PRESET_CONCERTHALL {  3900,   20,  29, 5000,  70, 100, 100, 250, 0,  5650,  80,  -9.8f }
#define FMOD_PRESET_CAVE {  2900,   15,  22, 5000, 100, 100, 100, 250, 0, 20000,  59, -11.3f }
#define FMOD_PRESET_ARENA {  7200,   20,  30, 5000,  33, 100, 100, 250, 0,  4500,  80,  -9.6f }
#define FMOD_PRESET_HANGAR { 10000,   20,  30, 5000,  23, 100, 100, 250, 0,  3400,  72,  -7.4f }
#define FMOD_PRESET_CARPETTEDHALLWAY {   300,    2,  30, 5000,  10, 100, 100, 250, 0,   500,  56, -24.0f }
#define FMOD_PRESET_HALLWAY {  1500,    7,  11, 5000,  59, 100, 100, 250, 0,  7800,  87,  -5.5f }
#define FMOD_PRESET_STONECORRIDOR {   270,   13,  20, 5000,  79, 100, 100, 250, 0,  9000,  86,  -6.0f }
#define FMOD_PRESET_ALLEY {  1500,    7,  11, 5000,  86, 100, 100, 250, 0,  8300,  80,  -9.8f }
#define FMOD_PRESET_FOREST {  1500,  162,  88, 5000,  54,  79, 100, 250, 0,   760,  94, -12.3f }
#define FMOD_PRESET_CITY {  1500,    7,  11, 5000,  67,  50, 100, 250, 0,  4050,  66, -26.0f }
#define FMOD_PRESET_MOUNTAINS {  1500,  300, 100, 5000,  21,  27, 100, 250, 0,  1220,  82, -24.0f }
#define FMOD_PRESET_QUARRY {  1500,   61,  25, 5000,  83, 100, 100, 250, 0,  3400, 100,  -5.0f }
#define FMOD_PRESET_PLAIN {  1500,  179, 100, 5000,  50,  21, 100, 250, 0,  1670,  65, -28.0f }
#define FMOD_PRESET_PARKINGLOT {  1700,    8,  12, 5000, 100, 100, 100, 250, 0, 20000,  56, -19.5f }
#define FMOD_PRESET_SEWERPIPE {  2800,   14,  21, 5000,  14,  80,  60, 250, 0,  3400,  66,   1.2f }
#define FMOD_PRESET_UNDERWATER {  1500,    7,  11, 5000,  10, 100, 100, 250, 0,   500,  92,   7.0f }

class FMOD {
    public:
    class ChannelControl {
        public:
        static void setReverbProperties(int channel, float amount);
    };
    class System {
        public:
        void setReverbProperties(int channel, FMOD_REVERB_PROPERTIES const*);
    };
};


class SoundModule : public Module {
    public:
    static FMOD::System* system;
    SoundModule(Module* parent, const char* id) : Module(parent,id){}

    virtual void initialize(){

        HookManager::addCallback(SYMBOL("mcpe","_ZN4FMOD6System18createChannelGroupEPKcPPNS_12ChannelGroupE"),LAMBDA((HookManager::CallbackController* controller,FMOD::System* b, const char* name,void* a),{
        Logger::debug("SoundModule", "%s", name);
        Logger::flush();
        system = b;
        },),HookManager::CALL | HookManager::LISTENER | HookManager::CONTROLLER | HookManager::RESULT);

    }

    static void setReverbProperties(int channel,float a,float b,float c,float d,float g,float h,float k, float l,float q, float w, float e,float r,float p){
        FMOD_REVERB_PROPERTIES reverb {a,b,c,g,h,k,l,q,w,e,r,p};
        system->setReverbProperties(channel, &reverb);
    };

    static void setReverbPreset(int channel){
        FMOD_REVERB_PROPERTIES reverb = {0,  2,  1.00f, -1000,  -454,   0,   0.40f,  0.83f, 1.0f,  -1646, 1};

        system->setReverbProperties(channel, &reverb);
    }
};


class SoundEngine {
    public:

};