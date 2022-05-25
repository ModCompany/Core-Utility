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

  #define FMOD_PRESET_OFF  {  0, -1,  1.00f, -10000, -10000, 0,   1.00f,  1.00f, 1.0f,  -2602, 0.007f,   200, 0.011f, 0.25f, 0.000f, 5000.0f, 250.0f,   0.0f,   0.0f, 0x33f }
  #define FMOD_PRESET_GENERIC  {  0,  0,  1.00f, -1000,  -100,   0,   1.49f,  0.83f, 1.0f,  -2602, 0.007f,   200, 0.011f, 0.25f, 0.000f, 5000.0f, 250.0f, 100.0f, 100.0f, 0x3f }
  #define FMOD_PRESET_PADDEDCELL  {  0,  1,  1.00f, -1000,  -6000,  0,   0.17f,  0.10f, 1.0f,  -1204, 0.001f,   207, 0.002f, 0.25f, 0.000f, 5000.0f, 250.0f, 100.0f, 100.0f, 0x3f }
  #define FMOD_PRESET_ROOM  {  }
  #define FMOD_PRESET_BATHROOM  {  0,  3,  1.00f, -1000,  -1200,  0,   1.49f,  0.54f, 1.0f,   -370, 0.007f,  1030, 0.011f, 0.25f, 0.000f, 5000.0f, 250.0f, 100.0f,  60.0f, 0x3f }
  #define FMOD_PRESET_LIVINGROOM  {  0,  4,  1.00f, -1000,  -6000,  0,   0.50f,  0.10f, 1.0f,  -1376, 0.003f, -1104, 0.004f, 0.25f, 0.000f, 5000.0f, 250.0f, 100.0f, 100.0f, 0x3f }
  #define FMOD_PRESET_STONEROOM  {  0,  5,  1.00f, -1000,  -300,   0,   2.31f,  0.64f, 1.0f,   -711, 0.012f,    83, 0.017f, 0.25f, 0.000f, 5000.0f, 250.0f, 100.0f, 100.0f, 0x3f }
  #define FMOD_PRESET_AUDITORIUM  {  0,  6,  1.00f, -1000,  -476,   0,   4.32f,  0.59f, 1.0f,   -789, 0.020f,  -289, 0.030f, 0.25f, 0.000f, 5000.0f, 250.0f, 100.0f, 100.0f, 0x3f }
  #define FMOD_PRESET_CONCERTHALL  {  0,  7,  1.00f, -1000,  -500,   0,   3.92f,  0.70f, 1.0f,  -1230, 0.020f,    -2, 0.029f, 0.25f, 0.000f, 5000.0f, 250.0f, 100.0f, 100.0f, 0x3f }
  #define FMOD_PRESET_CAVE  {  0,  8,  1.00f, -1000,  0,      0,   2.91f,  1.30f, 1.0f,   -602, 0.015f,  -302, 0.022f, 0.25f, 0.000f, 5000.0f, 250.0f, 100.0f, 100.0f, 0x1f }
  #define FMOD_PRESET_ARENA  {  0,  9,  1.00f, -1000,  -698,   0,   7.24f,  0.33f, 1.0f,  -1166, 0.020f,    16, 0.030f, 0.25f, 0.000f, 5000.0f, 250.0f, 100.0f, 100.0f, 0x3f }
  #define FMOD_PRESET_HANGAR  {  0,  10, 1.00f, -1000,  -1000,  0,   10.05f, 0.23f, 1.0f,   -602, 0.020f,   198, 0.030f, 0.25f, 0.000f, 5000.0f, 250.0f, 100.0f, 100.0f, 0x3f }
  #define FMOD_PRESET_CARPETTEDHALLWAY  {  0,  11, 1.00f, -1000,  -4000,  0,   0.30f,  0.10f, 1.0f,  -1831, 0.002f, -1630, 0.030f, 0.25f, 0.000f, 5000.0f, 250.0f, 100.0f, 100.0f, 0x3f }
  #define FMOD_PRESET_HALLWAY  {  0,  12, 1.00f, -1000,  -300,   0,   1.49f,  0.59f, 1.0f,  -1219, 0.007f,   441, 0.011f, 0.25f, 0.000f, 5000.0f, 250.0f, 100.0f, 100.0f, 0x3f }
  #define FMOD_PRESET_STONECORRIDOR  {  0,  13, 1.00f, -1000,  -237,   0,   2.70f,  0.79f, 1.0f,  -1214, 0.013f,   395, 0.020f, 0.25f, 0.000f, 5000.0f, 250.0f, 100.0f, 100.0f, 0x3f }
  #define FMOD_PRESET_ALLEY  {  0,  14, 0.30f, -1000,  -270,   0,   1.49f,  0.86f, 1.0f,  -1204, 0.007f,    -4, 0.011f, 0.25f, 0.000f, 5000.0f, 250.0f, 100.0f, 100.0f, 0x3f }
  #define FMOD_PRESET_FOREST  {  0,  15, 0.30f, -1000,  -3300,  0,   1.49f,  0.54f, 1.0f,  -2560, 0.162f,  -229, 0.088f, 0.25f, 0.000f, 5000.0f, 250.0f,  79.0f, 100.0f, 0x3f }
  #define FMOD_PRESET_CITY  {  0,  16, 0.50f, -1000,  -800,   0,   1.49f,  0.67f, 1.0f,  -2273, 0.007f, -1691, 0.011f, 0.25f, 0.000f, 5000.0f, 250.0f,  50.0f, 100.0f, 0x3f }
  #define FMOD_PRESET_MOUNTAINS  {  0,  17, 0.27f, -1000,  -2500,  0,   1.49f,  0.21f, 1.0f,  -2780, 0.300f, -1434, 0.100f, 0.25f, 0.000f, 5000.0f, 250.0f,  27.0f, 100.0f, 0x1f }
  #define FMOD_PRESET_QUARRY  {  0,  18, 1.00f, -1000,  -1000,  0,   1.49f,  0.83f, 1.0f, -10000, 0.061f,   500, 0.025f, 0.25f, 0.000f, 5000.0f, 250.0f, 100.0f, 100.0f, 0x3f }
  #define FMOD_PRESET_PLAIN  {  0,  19, 0.21f, -1000,  -2000,  0,   1.49f,  0.50f, 1.0f,  -2466, 0.179f, -1926, 0.100f, 0.25f, 0.000f, 5000.0f, 250.0f,  21.0f, 100.0f, 0x3f }
  #define FMOD_PRESET_PARKINGLOT  {  0,  20, 1.00f, -1000,  0,      0,   1.65f,  1.50f, 1.0f,  -1363, 0.008f, -1153, 0.012f, 0.25f, 0.000f, 5000.0f, 250.0f, 100.0f, 100.0f, 0x1f }
  #define FMOD_PRESET_SEWERPIPE  {  0,  21, 0.80f, -1000,  -1000,  0,   2.81f,  0.14f, 1.0f,    429, 0.014f,  1023, 0.021f, 0.25f, 0.000f, 5000.0f, 250.0f,  80.0f,  60.0f, 0x3f }
  #define FMOD_PRESET_UNDERWATER  {  0,  22, 1.00f, -1000,  -4000,  0,   1.49f,  0.10f, 1.0f,   -449, 0.007f,  1700, 0.011f, 1.18f, 0.348f, 5000.0f, 250.0f, 100.0f, 100.0f, 0x3f }
  #define FMOD_PRESET_PSP_ROOM  {  0,  1,  0,     0,      0,      0,   0.0f,   0.0f,  0.0f,     0,  0.000f,     0, 0.000f, 0.00f, 0.000f, 0000.0f,   0.0f,  0.0f,    0.0f, 0x31f }
  #define FMOD_PRESET_PSP_STUDIO_A  {  0,  2,  0,     0,      0,      0,   0.0f,   0.0f,  0.0f,     0,  0.000f,     0, 0.000f, 0.00f, 0.000f, 0000.0f,   0.0f,  0.0f,    0.0f, 0x31f }
  #define FMOD_PRESET_PSP_STUDIO_B  {  0,  3,  0,     0,      0,      0,   0.0f,   0.0f,  0.0f,     0,  0.000f,     0, 0.000f, 0.00f, 0.000f, 0000.0f,   0.0f,  0.0f,    0.0f, 0x31f }
  #define FMOD_PRESET_PSP_STUDIO_C  {  0,  4,  0,     0,      0,      0,   0.0f,   0.0f,  0.0f,     0,  0.000f,     0, 0.000f, 0.00f, 0.000f, 0000.0f,   0.0f,  0.0f,    0.0f, 0x31f }
  #define FMOD_PRESET_PSP_HALL  {  0,  5,  0,     0,      0,      0,   0.0f,   0.0f,  0.0f,     0,  0.000f,     0, 0.000f, 0.00f, 0.000f, 0000.0f,   0.0f,  0.0f,    0.0f, 0x31f }
  #define FMOD_PRESET_PSP_SPACE  {  0,  6,  0,     0,      0,      0,   0.0f,   0.0f,  0.0f,     0,  0.000f,     0, 0.000f, 0.00f, 0.000f, 0000.0f,   0.0f,  0.0f,    0.0f, 0x31f }
  #define FMOD_PRESET_PSP_ECHO  {  0,  7,  0,     0,      0,      0,   0.0f,   0.0f,  0.0f,     0,  0.000f,     0, 0.000f, 0.00f, 0.000f, 0000.0f,   0.0f,  0.0f,    0.0f, 0x31f }
  #define FMOD_PRESET_PSP_DELAY  {  0,  8,  0,     0,      0,      0,   0.0f,   0.0f,  0.0f,     0,  0.000f,     0, 0.000f, 0.00f, 0.000f, 0000.0f,   0.0f,  0.0f,    0.0f, 0x31f }
  #define FMOD_PRESET_PSP_PIPE  {  0,  9,  0,     0,      0,      0,   0.0f,   0.0f,  0.0f,     0,  0.000f,     0, 0.000f, 0.00f, 0.000f, 0000.0f,   0.0f,  0.0f,    0.0f, 0x31f }

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

        HookManager::addCallback(SYMBOL("mcpe","_ZN4FMOD6System18createChannelGroupEPKcPPNS_12ChannelGroupE"),LAMBDA((HookManager::CallbackController* controller,FMOD::System* b,char* name,void* a),{
        Logger::debug("SoundModule", "%s", name);
        Logger::flush();
        system = b;
        },),HookManager::CALL | HookManager::LISTENER | HookManager::CONTROLLER | HookManager::RESULT);

    }

    static void setReverbProperties(int channel,float a,float b,float c,float d,float g,float h,float k, float l,float q, float w, float e,float r){
        FMOD_REVERB_PROPERTIES reverb {a,b,c,g,h,k,l,q,w,e,r};
        system->setReverbProperties(channel, &reverb);
    };

    static void setReverbPreset(int channel){
        FMOD_REVERB_PROPERTIES reverb = {0,  2,  1.00f, -1000,  -454,   0,   0.40f,  0.83f, 1.0f,  -1646, 1};

        system->setReverbProperties(channel, &reverb);
    }
};