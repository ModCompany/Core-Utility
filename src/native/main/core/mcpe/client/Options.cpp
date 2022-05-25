#include <innercore_callbacks.h>
#include <client/Options.h>

extern "C" {
	JNIEXPORT jint JNICALL Java_com_core_api_mcpe_client_Options_getUiProfilePointer
	(JNIEnv* env, jclass, jlong pointer) {
        return (jint) ((int) ((Options*) pointer)->getUIProfile());
	}
}