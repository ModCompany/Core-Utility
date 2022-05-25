#include <innercore/global_context.h>
#include <innercore_callbacks.h>
#include <java.h>
export(jlong,innnercore_GlobalContext_getClientInstacePointer){
    return (jlong) GlobalContext::getMinecraftClient();
}
export(jlong,innnercore_GlobalContext_getServerPlayerPointer){
	return (jlong) GlobalContext::getServerPlayer();
}
export(jlong,innnercore_GlobalContext_getLocalPlayerPointer){
	return (jlong) GlobalContext::getLocalPlayer();
}
export(jlong,innnercore_GlobalContext_getServerLevelPointer){
	return (jlong) GlobalContext::getServerLevel();
}
export(jlong,innnercore_GlobalContext_getLevelPointer){
	return (jlong) GlobalContext::getLevel();
}
