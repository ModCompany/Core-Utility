#include <innercore/item_registry.h>
#include <innercore_callbacks.h>
#include <java.h>

export(jlong, module_ItemsUtil_getItemById, jint id){
    return (jlong) ItemRegistry::getItemById((int) id);
}