#include <innercore/id_pool.h>
#include <innercore/block_registry.h>
#include <innercore_callbacks.h>
#include <java.h>
#include <core/module/BlockUtils.h>
#include <hook.h>
#include <symbol.h>

jclass BlockUtils::BlockUtilsJava;
jmethodID BlockUtils::renderModelBlock;

class Tessellator;
class Block;
class BlockPos;

void BlockUtils::init(){
    JNIEnv* env;
	ATTACH_JAVA(env, JNI_VERSION_1_6){
        BlockUtils::BlockUtilsJava = reinterpret_cast<jclass>(env->NewGlobalRef(env->FindClass("com/core/api/innnercore/BlockUtils")));
        BlockUtils::renderModelBlock = env->GetStaticMethodID(BlockUtils::BlockUtilsJava, "renderModelBlock", "(JJJ)V");
    }
    HookManager::addCallback(
        SYMBOL("mcpe", "_ZN16BlockTessellator17tessellateInWorldER11TessellatorRK5BlockRK8BlockPosRK22TextureUVCoordinateSet"), 
        LAMBDA((void* blockTessellator, Tessellator& tessellator, Block const& block, BlockPos const& pos, TextureUVCoordinateSet const&), {
            JNIEnv* env;
	        ATTACH_JAVA(env, JNI_VERSION_1_6){
                env->CallStaticVoidMethod(
                    BlockUtils::BlockUtilsJava, BlockUtils::renderModelBlock,
                    (jlong) &tessellator, (jlong) &block, (jlong) &pos
                );
            }
        }, ), HookManager::CALL | HookManager::LISTENER
    );
}

export(jlong, innnercore_BlockUtils_getBlockLegacy, jint id) {
    return (jlong) BlockRegistry::getBlockById((int) id);
}
export(jlong, innnercore_BlockUtils_getBlockState, jint id, jint data) {
    return (jlong) BlockRegistry::getBlockStateForIdData((int) id, (int) data);
}