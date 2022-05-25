#include <innercore_callbacks.h>
#include <client/Options.h>
#include <java.h>
export(jint,mcpe_client_Options_getUiProfilePointer,jlong pointer) {
	return (jint) ((int) ((Options*) pointer)->getUIProfile());
}
