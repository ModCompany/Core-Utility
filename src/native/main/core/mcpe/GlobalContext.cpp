#include <innercore/global_context.h>
#include <innercore_callbacks.h>

extern "C" {
	JNIEXPORT jlong JNICALL Java_com_core_api_innnercore_GlobalContext_getClientInstacePointer
	(JNIEnv* env, jclass) {
        return (jlong) GlobalContext::getMinecraftClient();
	}
    JNIEXPORT jlong JNICALL Java_com_core_api_innnercore_GlobalContext_getServerPlayerPointer
	(JNIEnv* env, jclass) {
        return (jlong) GlobalContext::getServerPlayer();
	}
    JNIEXPORT jlong JNICALL Java_com_core_api_innnercore_GlobalContext_getLocalPlayerPointer
	(JNIEnv* env, jclass) {
        return (jlong) GlobalContext::getLocalPlayer();
	}
    JNIEXPORT jlong JNICALL Java_com_core_api_innnercore_GlobalContext_getServerLevelPointer
	(JNIEnv* env, jclass) {
        return (jlong) GlobalContext::getServerLevel();
	}
    JNIEXPORT jlong JNICALL Java_com_core_api_innnercore_GlobalContext_getLevelPointer
	(JNIEnv* env, jclass) {
        return (jlong) GlobalContext::getLevel();
	}
}