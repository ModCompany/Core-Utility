#include <innercore_callbacks.h>
#include <java.h>
#include <nativejs.h>

#include <stl/string>
#define stl std::__ndk1

#include <client/ClientIntance.h>
#include <client/Options.h>
#include <innercore/global_context.h>

export(void, client_Options_setRenderMobInfoState, jboolean a){
    Options* option = GlobalContext::getMinecraftClient()->getOptions();
    option->setDevRenderMobInfoState(a);
   // option->set
}

export(jint,mcpe_client_Options_getUiProfilePointer,jlong pointer) {
	return (jint) ((int) ((Options*) pointer)->getUIProfile());
}
