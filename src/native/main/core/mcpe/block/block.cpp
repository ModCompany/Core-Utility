
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

#include <core/item/ItemProvider.h>
#include <core/block/BlockProvider.h>
#include <core/BlockItemRegistry.h>

 
void DoorFactory::registerBlock() {
    if (id != 0) {
        BlockRegistry::registerCustomBlock<DoorBlock>(new DoorProvider(this), IdConversion::staticToDynamic(id, IdConversion::BLOCK), nameId, *props.getMaterial(),DoorBlock::DoorType::Oak);
    }
}

#include <block/Block.h>

export(void,engine_BlockRegistry_registerDoorBlock,jint id,jstring uid,jstring name,jstring texture,jint data){

	auto factory = new DoorFactory(JavaClass::toString(env,name),JavaClass::toString(env,texture),data);
	factory->initParameters(id, JavaClass::toString(env,uid));
	LegacyBlockRegistry::registerBlockFactory(factory);

	Logger::debug("test", "test block registered!");
	LegacyItemRegistry::addItemToCreative(id, 1, 0, nullptr);


} 
