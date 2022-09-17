
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
#include <type/Json.h>

#include <horizon/types.h>

#include <horizon/item.h>



#include <innercore/item_registry.h>
#include <innercore/legacy_item_registry.h>
#include <innercore/block_registry.h>
#include <innercore/legacy_block_registry.h>
#include <innercore/id_conversion_map.h>
#include <core/JavaClass.h>
typedef int content_id_t;

#include <block/BlockLegacy.h>

class ItemState;
class VanillaStates {
	public:
	static ItemState DoorHingeBit;
	static ItemState DirtType;
	static ItemState UpperBlockBit;
	static ItemState Direction;
	static ItemState OpenBit;
};
class BlockSource;
class Random;
class BlockSupportType;
class Material {};

class DoorFactory : public LegacyBlockRegistry::LegacyBlockFactoryBase {
	public:
	std::string name;
	std::string texture;
	int texture_data;

	
	DoorFactory(std::string name,std::string texture,int id) : LegacyBlockRegistry::LegacyBlockFactoryBase() {
		this->name = name;
		this->texture = texture;
		this->texture_data = id;
	}	
    virtual void registerBlock();
	virtual void applyProperties(){
		//this->block->addState(VanillaStates::DoorHingeBit);
		//this->block->addState(VanillaStates::Direction);
		//this->block->addState(VanillaStates::OpenBit);
		//this->block->addState(VanillaStates::UpperBlockBit);
	}
};

class DoorProvider : public LegacyBlockRegistry::LegacyBlockProviderBase {
public:
    DoorFactory* factory;
 
    DoorProvider(DoorFactory* factory) : LegacyBlockRegistry::LegacyBlockProviderBase() {
        this->factory = factory;
		this->factory->props.translucency = 0.8;
		this->factory->props.renderLayer = 8;
		this->factory->props.renderType = 7;
		this->factory->addVariant(this->factory->name,true)->textureData = FaceTextureData(this->factory->name,this->factory->texture_data);
    };

    virtual LegacyBlockRegistry::LegacyBlockFactoryBase* getFactory() {
        return this->factory;
    }
	
	
	virtual void patchVtable(void** vtable){
		//
	}
	virtual void onBlockItemCreated(){

		//ItemRegistry::registerCustomItem<BowItem>(new BowProvider(this),IdConversion::staticToDynamic(id, IdConversion::ITEM), nameId);
	}
	
};
 
void DoorFactory::registerBlock() {
    if (id != 0) {
        BlockRegistry::registerCustomBlock<DoorBlock>(new DoorProvider(this), IdConversion::staticToDynamic(id, IdConversion::BLOCK), nameId, *props.getMaterial(),DoorBlock::DoorType::LEFT);
    }
}



#include <block/Block.h>

export(void,engine_BlockRegistry_registerDoorBlock,jint id,jstring uid,jstring name,jstring texture,jint data){
	auto factory = new DoorFactory(JavaClass::toString(env,name),JavaClass::toString(env,texture),data);
	factory->initParameters(id, JavaClass::toString(env,uid));
	LegacyBlockRegistry::registerBlockFactory(factory);
	LegacyItemRegistry::addItemToCreative(id, 1, 0, nullptr);
	Logger::debug("test", "test block registered!");
} 
