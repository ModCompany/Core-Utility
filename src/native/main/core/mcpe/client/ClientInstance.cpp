
#include <horizon/types.h>
#include <innercore/global_context.h>
#include <innercore_callbacks.h>
#include <client/ClientIntance.h>
#include <client/Options.h>
#include <entity/Entity.h>
#include <type/AutomaticID.h>
#include <level/render/LevelRendererPlayer.h>
#include <vtable.h>
#include <java.h>
export(jlong,mcpe_client_ClientInstance_getOptionsPointer,jlong pointer) {
	VTABLE_FIND_OFFSET(ClientInstance_getOptions, _ZTV14ClientInstance, _ZNK14ClientInstance10getOptionsEv);
	return (jlong) VTABLE_CALL<Options*>(ClientInstance_getOptions, (ClientInstance*) pointer);
}

export(jlong, mcpe_client_ClientInstance_getGuiPointer,jlong pointer){
	return (jlong) ((ClientInstance*) pointer)->getGuiData();
}

export(void, mcpe_client_ClientInstance_setCameraEntity, jlong pointer, jlong entity){
	return ((ClientInstance*) pointer)->setCameraEntity(Actor::wrap(entity));
}

export(void, mcpe_client_ClientInstance_renderDestroyBlock,jlong pointer, jint x,jint y,jint z,jfloat speed){
	((ClientInstance*) pointer)->getLevelRenderer()->getLevelRendererPlayer()->addDestroyBlock({(int)x,(int)y,(int)z},speed);
	((ClientInstance*) pointer)->getLevelRenderer()->getLevelRendererPlayer()->updateDestroyProgress();
}
