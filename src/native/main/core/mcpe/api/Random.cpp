#include <Core.h>
#include <innercore_callbacks.h>

extern "C" {
	JNIEXPORT jint JNICALL Java_com_core_api_mcpe_api_Random_nextIntPointer
	(JNIEnv* env, jclass, jlong pointer, jint max) {
        return (jint) ((Core::Random*) pointer)->nextInt(max);
	}
}