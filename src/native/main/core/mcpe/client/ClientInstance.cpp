#include <innercore/global_context.h>
#include <innercore_callbacks.h>
#include <client/Options.h>
#include <vtable.h>

extern "C" {
	JNIEXPORT jlong JNICALL Java_com_core_api_mcpe_client_ClientInstance_getOptionsPointer
	(JNIEnv* env, jclass, jlong pointer) {
        VTABLE_FIND_OFFSET(ClientInstance_getOptions, _ZTV14ClientInstance, _ZNK14ClientInstance10getOptionsEv);
        return (jlong) VTABLE_CALL<Options*>(ClientInstance_getOptions, (ClientInstance*) pointer);
	}
}