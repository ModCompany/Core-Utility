#include <hook.h>
#include <mod.h>
#include <logger.h>
#include <symbol.h>
#include <innercore_callbacks.h>
#include <nativejs.h>
#include <vtable.h>
#include <string>

#define stl std


class LocalizationModule : public Module {
    public:
    LocalizationModule(Module* module, const char* id) : Module(module,id){}

    virtual void initialize(){
        
    };
};