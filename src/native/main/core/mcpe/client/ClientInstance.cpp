#include <innercore/global_context.h>
#include <innercore_callbacks.h>
#include <client/ClientIntance.h>
#include <client/Options.h>

#include <vtable.h>
#include <java.h>

#include <innercore/global_context.h>
#include <entity/Entity.h>
#include <type/AutomaticID.h>

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