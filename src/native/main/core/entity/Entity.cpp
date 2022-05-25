#include <entity/Entity.h>
#include <level/api/Vec3.h>
#include <vtable.h>

void Actor::setPosVTABLE(Vec3& pos){
    VTABLE_FIND_OFFSET(Actor_setPos, _ZTV5Actor, _ZN5Actor6setPosERK4Vec3);
    VTABLE_CALL<void*>(Actor_setPos, this, pos);
}

std::string Actor::getEntityTypeVTABLE(){
    VTABLE_FIND_OFFSET(Actor_getEntityTypeId, _ZTV5Actor, _ZNK5Actor15getEntityTypeIdEv);
    return std::string((VTABLE_CALL<std::__ndk1::string&>(Actor_getEntityTypeId, this)).c_str());
}