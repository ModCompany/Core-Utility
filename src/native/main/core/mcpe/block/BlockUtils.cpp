#include <innercore/id_pool.h>
#include <innercore/block_registry.h>
#include <innercore_callbacks.h>
#include <java.h>

export(jlong, innnercore_BlockUtils_getBlockLegacy, jint id) {
    return (jlong) BlockRegistry::getBlockById((int) id);
}
export(jlong, innnercore_BlockUtils_getBlockState, jint id, jint data) {
    return (jlong) BlockRegistry::getBlockStateForIdData((int) id, (int) data);
}