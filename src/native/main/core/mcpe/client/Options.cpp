#include <innercore_callbacks.h>
#include <java.h>
#include <nativejs.h>

#include <string>
#define stl std

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
