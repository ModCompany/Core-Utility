#pragma once

#include <type/Json.h>

#include <horizon/types.h>

#include <horizon/item.h>
#include <vtable.h>


#include <innercore/item_registry.h>
#include <innercore/legacy_item_registry.h>
#include <innercore/block_registry.h>
#include <innercore/legacy_block_registry.h>
#include <innercore/id_conversion_map.h>
#include <core/JavaClass.h>
typedef int content_id_t;
#include <core/BlockItemRegistry.h>

#include <block/BlockLegacy.h>
class CustomDoorItem : public DoorItem {
	public:
	char filler[256];
	DoorBlock* block;
	CustomDoorItem(DoorBlock* block,stl::string const& uid,int id, DoorBlock::DoorType type) : DoorItem(uid,id,type){
		this->block = block;
	};

	DoorBlock* getDoorBlock() const{
		Logger::debug("CoreBlock","flush");
		Logger::flush();
		return block;
	};



};

class DoorFactory : public LegacyBlockRegistry::LegacyBlockFactoryBase {
	public:
	std::string name;
	std::string texture;
	int texture_data;
	DoorBlock* door_block;	
	DoorFactory(std::string name,std::string texture,int id) : LegacyBlockRegistry::LegacyBlockFactoryBase() {
		this->name = name;
		this->texture = texture;
		this->texture_data = id;
	}	

    virtual void registerBlock();
	virtual void applyProperties(){
		this->block->addState(VanillaStates::DoorHingeBit);
		this->block->addState(VanillaStates::Direction);
		this->block->addState(VanillaStates::OpenBit);
		this->block->addState(VanillaStates::UpperBlockBit);
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
		this->factory->addVariant(this->factory->name,true);
    };
    virtual LegacyBlockRegistry::LegacyBlockFactoryBase* getFactory() {
        return this->factory;
    }
	virtual void patchVtable(void** vtable){
		//
	}

	static DoorBlock* getDoorBlock(DoorItem* self) {

		return BlockItemPool::getBlock<DoorBlock>((int)self->getId());
	};
	
	virtual void onBlockItemCreated(){
		
		DoorItem* door = new DoorItem("test_block",this->factory->id,DoorBlock::DoorType::Oak);
		void* ptr = (void*) door;
		void** table = (void**) ptr;
		LegacyBlockRegistry::LegacyBlockProviderBase::patchItemVtable(table);
		ItemRegistry::registerItem((Item*)door,nullptr);


	}
};


