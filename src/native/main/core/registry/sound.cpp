#include <hook.h>
#include <mod.h>
#include <logger.h>
#include <symbol.h>
#include <innercore_callbacks.h>
#include <nativejs.h>
#include <vtable.h>
#include <stl/string>

#define stl std::__ndk1

#include "sound.h"



FMOD::System* SoundModule::system;

JS_MODULE_VERSION(NativeSound, 1);

JS_EXPORT_COMPLEX(NativeSound, setReverb, "V(FF)", (JNIEnv* env,NativeJS::ComplexArgs& obj){
  float a = obj.get("decayTime").asFloat(1);
  float b = obj.get("earlyDelay").asFloat(1);
  float c = obj.get("lateDelay").asFloat(1);
  float d = obj.get("hfReference").asFloat(1);
  float e = obj.get("hfDecayRation").asFloat(1);
  float f = obj.get("diffusion").asFloat(1);
  float g = obj.get("density").asFloat(1);
  float h = obj.get("lowShelfFreq").asFloat(1);
  float j = obj.get("lowShelfGain").asFloat(1);
  float k = obj.get("highCut").asFloat(1);
  float l = obj.get("earlyLateMix").asFloat(1);
  float q = obj.get("wet").asFloat(1);
  int channel = obj.get("channel").asInt(1);
  SoundModule::setReverbProperties(channel,a,b,c,d,e,f,g,h,j,k,l,q);
  return 0;
});

JS_EXPORT(NativeSound, setReverbPreset, "V(II)",(JNIEnv* env, int channel, int preset){
    SoundModule::setReverbPreset(channel);
});