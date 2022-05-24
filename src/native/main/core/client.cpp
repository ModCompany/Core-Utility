
#include <hook.h>
#include <mod.h>
#include <logger.h>
#include <symbol.h>
#include <innercore_callbacks.h>
#include <nativejs.h>
#include <vtable.h>
#include <java.h>
#include <stl/string>
#define stl std::__ndk1

#include <innercore/global_context.h>
#include <client/ClientIntance.h>
#include <client/Options.h>
export(void, client_Options_setRenderMobInfoState, jboolean a){
    Options* option = GlobalContext::getMinecraftClient()->getOptions();
    option->setDevRenderMobInfoState(a);
   // option->set
}

JS_MODULE_VERSION(Govno, 1);



JS_EXPORT(Govno, debug, "V()",(JNIEnv* env){
    Options* option = GlobalContext::getMinecraftClient()->getOptions();
    option->setDevRenderMobInfoState(true);
    option->setDevRenderBoundingBoxes(true);
    option->setDevRenderPaths(true);

});



JS_EXPORT(Govno, setDebug, "V()",(JNIEnv* env, int debug){
    Options* option = GlobalContext::getMinecraftClient()->getOptions();
    option->setRenderDebug((DebugHudOptions) debug);

});