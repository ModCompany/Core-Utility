#include <innercore/id_pool.h>
#include <innercore/block_registry.h>
#include <innercore_callbacks.h>
#include <java.h>
#include <core/module/BlockLegacy.h>
#include <block/BlockLegacy.h>
#include <hook.h>
#include <symbol.h>
#include <ui/Tessellator.h>
#include <logger.h>
#include <core/JavaClass.h>
#include <core/VtableHelper.h>

export(void, mcpe_block_BlockLegacy_addState, jlong pointer, jstring name, jint min, jint max, jint v) {

    //((BlockLegacy*) pointer)->addState(*state, (int) v);
}

void BlockLegacyApi::init() {
    
    /*HookManager::addCallback(
        SYMBOL("mcpe","_ZN16BlockTessellator17tessellateInWorldER11TessellatorRK5BlockRK8BlockPosb"), 
        LAMBDA((void* self, Tessellator& tessellator),{
            Logger::debug("CORE", tessellator.material.getHashedName().c_str());
	    },
    ),HookManager::CALL | HookManager::LISTENER);
    Артём или Артём, вот в чём вопрос
    HookManager::addCallback(
        SYMBOL("mcpe","_ZN11Tessellator16triggerInterceptERKN3mce11MaterialPtrERKNS0_10TexturePtrE"), 
        LAMBDA((Tessellator* self, mce::MaterialPtr const& material, mce::TexturePtr const& texture),{
            Logger::debug("_____CORE", material.getHashedName().c_str());
	    },
    ),HookManager::CALL | HookManager::LISTENER);*/
}