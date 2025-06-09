#pragma once

#include <vtable.h>

class IClientInstance {};

enum UIProfile : int {};
class Options {
    public:
        UIProfile getUIProfile() const;
        float getInterfaceOpacity() const;
};
class ClientInstance : public IClientInstance {
    public:
        inline Options* getOptionsVTABLE(){
            VTABLE_FIND_OFFSET(ClientInstance_getOptions, _ZTV14ClientInstance, _ZNK14ClientInstance10getOptionsEv);
            return VTABLE_CALL<Options*>(ClientInstance_getOptions, this);
        }
};