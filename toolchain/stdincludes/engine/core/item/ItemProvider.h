#pragma once

#include <hook.h>
#include <mod.h>
#include <logger.h>
#include <symbol.h>
#include <innercore_callbacks.h>
#include <nativejs.h>
#include <vtable.h>
#include <stl/string>

#include <type/Json.h>
#include <horizon/types.h>
#include <horizon/item.h>

#include <innercore/common.h>
#include <innercore/item_registry.h>
#include <innercore/legacy_item_registry.h>
#include <innercore/id_conversion_map.h>

#include <core/JavaClass.h>
#include <core/VtableHelper.h>
#include <core/Overrided.h>

#include <mce.h>
#include <block/Block.h>
#include <block/BlockLegacy.h>
#include <core/BlockItemRegistry.h>


class BowFactory : public LegacyItemRegistry::LegacyItemFactoryBase
{
public:
	BowFactory() : LegacyItemRegistry::LegacyItemFactoryBase(){};
	virtual void registerItem();
};

class BowProvider : public LegacyItemRegistry::LegacyItemProviderBase
{
public:
	BowFactory *factory;
	BowProvider(BowFactory *factory) : LegacyItemRegistry::LegacyItemProviderBase()
	{
		this->factory = factory;
		factory->props.durability = 10;
	}

	virtual LegacyItemRegistry::LegacyItemFactoryBase *getFactory()
	{
		return this->factory;
	}
	virtual void setupVtable(void *a)
	{
		// LegacyItemRegistry::LegacyItemProviderBase::setupVtable(a);
		//
		//	void** table = *(void***) a;
		void **table = (void **)a;

		if (this->factory->item != nullptr)
		{
			void **table = *(void ***)factory->item;
			table[getVtableOffset("_ZTV7BowItem", "_ZNK16RangedWeaponItem3useER9ItemStackR6Player")] = SYMBOL("mcpe", "_ZNK16RangedWeaponItem3useER9ItemStackR6Player");
			table[getVtableOffset("_ZTV7BowItem", "_ZNK4Item6_useOnER9ItemStackR5Actor8BlockPoshfff")] = SYMBOL("mcpe", "_ZNK4Item6_useOnER9ItemStackR5Actor8BlockPoshfff");
			table[getVtableOffset("_ZTV7BowItem", "_ZNK16RangedWeaponItem9mineBlockER9ItemStackRK5BlockiiiP5Actor")] = SYMBOL("mcpe", "_ZNK16RangedWeaponItem9mineBlockER9ItemStackRK5BlockiiiP5Actor");
			table[getVtableOffset("_ZTV7BowItem", "_ZNK16RangedWeaponItem12releaseUsingER9ItemStackP6Playeri")] = SYMBOL("mcpe", "_ZNK16RangedWeaponItem12releaseUsingER9ItemStackP6Playeri");
		}
	}
};


/*
JS_EXPORT(Test, registerBow, "V(I)", (JNIEnv* env,int id){
	BowFactory* factory = new BowFactory();
	factory->initParameters(id, "test_bow", "Test Bow", "stick", 0);
	LegacyItemRegistry::registerItemFactory(factory);
})
*/

class Level;
class BlockSource;


class ShieldFactory : public LegacyItemRegistry::LegacyItemFactoryBase
{
public:
	ShieldFactory() : LegacyItemRegistry::LegacyItemFactoryBase(){};
	virtual void registerItem();
};

class ShieldProvider : public LegacyItemRegistry::LegacyItemProviderBase
{
public:
	ShieldFactory *factory;
	ShieldProvider(ShieldFactory *factory) : LegacyItemRegistry::LegacyItemProviderBase()
	{
		this->factory = factory;
		factory->props.durability = 10;
	}

	virtual LegacyItemRegistry::LegacyItemFactoryBase *getFactory()
	{
		return this->factory;
	}
	virtual void setupVtable(void *a)
	{
		// LegacyItemRegistry::LegacyItemProviderBase::setupVtable(a);

		if (this->factory->item != nullptr)
		{

			void **table = *(void ***)factory->item;
			// table[getVtableOffset("_ZTV10ShieldItem", "_ZNK16RangedWeaponItem3useER9ItemStackR6Player")] = SYMBOL("mcpe", "_ZNK16RangedWeaponItem3useER9ItemStackR6Player");
			// table[getVtableOffset("_ZTV10ShieldItem", "_ZNK4Item6_useOnER9ItemStackR5Actor8BlockPoshfff")] = SYMBOL("mcpe", "_ZNK4Item6_useOnER9ItemStackR5Actor8BlockPoshfff");
			// table[getVtableOffset("_ZTV10ShieldItem","_ZNK16RangedWeaponItem9mineBlockER9ItemStackRK5BlockiiiP5Actor")] = SYMBOL("mcpe","_ZNK16RangedWeaponItem9mineBlockER9ItemStackRK5BlockiiiP5Actor");
			// table[getVtableOffset("_ZTV10ShieldItem","_ZNK16RangedWeaponItem12releaseUsingER9ItemStackP6Playeri")] = SYMBOL("mcpe", "_ZNK16RangedWeaponItem12releaseUsingER9ItemStackP6Playeri");
		}
	}
};



class FishingFactory : public LegacyItemRegistry::LegacyItemFactoryBase
{
public:
	FishingFactory() : LegacyItemRegistry::LegacyItemFactoryBase(){};
	virtual void registerItem();
};

class FishingProvider : public LegacyItemRegistry::LegacyItemProviderBase
{
public:
	FishingFactory *factory;
	FishingProvider(FishingFactory *factory) : LegacyItemRegistry::LegacyItemProviderBase()
	{
		this->factory = factory;
	}

	virtual LegacyItemRegistry::LegacyItemFactoryBase *getFactory()
	{
		return this->factory;
	}

	virtual void setupVtable(void *a)
	{
		// LegacyItemRegistry::LegacyItemProviderBase::setupVtable(a);
		void **table = (void **)a;
		// table[getVtableOffset("_ZTV14FishingRodItem", "_ZNK14FishingRodItem3useER9ItemStackR6Player")] = SYMBOL("mcpe", "_ZNK14FishingRodItem3useER9ItemStackR6Player");
		// table[getVtableOffset("_ZTV14FishingRodItem", "_ZNK4Item6_useOnER9ItemStackR5Actor8BlockPoshfff")] = SYMBOL("mcpe", "_ZNK4Item6_useOnER9ItemStackR5Actor8BlockPoshfff");
		// table[getVtableOffset("_ZTV14FishingRodItem", "_ZNK4Item20validFishInteractionEi")] = SYMBOL("mcpe", "_ZNK4Item20validFishInteractionEi");
		// table[getVtableOffset("_ZTV14FishingRodItem", "_ZNK14FishingRodItem16requiresInteractEv")] = SYMBOL("mcpe", "_ZNK14FishingRodItem16requiresInteractEv");
	}
};


#include <stl/vector>


class DoorItem : public Item {
	public:
	char filler[256];
	DoorItem(stl::string const&,int,DoorBlock::DoorType);
	Block const& getDoorBlock() const;
};

class DoorItemFactory : public LegacyItemRegistry::LegacyItemFactoryBase
{
public:
	DoorItemFactory() : LegacyItemRegistry::LegacyItemFactoryBase(){};
	virtual void registerItem();
};

class DoorItemProvider : public LegacyItemRegistry::LegacyItemProviderBase
{
public:
	DoorItemFactory *factory;
	DoorItemProvider(DoorItemFactory *factory) : LegacyItemRegistry::LegacyItemProviderBase(){
		this->factory = factory;
	}
	virtual LegacyItemRegistry::LegacyItemFactoryBase *getFactory(){
		return this->factory;
	}

	virtual void setupVtable(void *a)
	{
		// LegacyItemRegistry::LegacyItemProviderBase::setupVtable(a);
		void **table = (void **)a;
		// table[getVtableOffset("_ZTV14FishingRodItem", "_ZNK14FishingRodItem3useER9ItemStackR6Player")] = SYMBOL("mcpe", "_ZNK14FishingRodItem3useER9ItemStackR6Player");
		// table[getVtableOffset("_ZTV14FishingRodItem", "_ZNK4Item6_useOnER9ItemStackR5Actor8BlockPoshfff")] = SYMBOL("mcpe", "_ZNK4Item6_useOnER9ItemStackR5Actor8BlockPoshfff");
		// table[getVtableOffset("_ZTV14FishingRodItem", "_ZNK4Item20validFishInteractionEi")] = SYMBOL("mcpe", "_ZNK4Item20validFishInteractionEi");
		// table[getVtableOffset("_ZTV14FishingRodItem", "_ZNK14FishingRodItem16requiresInteractEv")] = SYMBOL("mcpe", "_ZNK14FishingRodItem16requiresInteractEv");
	}
};

class ItemModule : public Module {
	public:
	ItemModule(Module* parent,const char* name) : Module(parent,name){};
	virtual void initialize(){
		HookManager::addCallback(SYMBOL("mcpe", "_ZNK8DoorItem12getDoorBlockEv"), LAMBDA((HookManager::CallbackController * controller, DoorItem *a), {
			short id = a->getId();
			if(BlockItemPool::check(id,BlockItemPool::FLAGS::Block)){

				Logger::debug("CoreTest","Find %i",id);
				Logger::flush();
				return BlockItemPool::getBlock<DoorBlock>(id)->getDefaultState();
			}
			
			return controller->call<Block*>(a->getDoorBlock());

		},),HookManager::CALL | HookManager::REPLACE | HookManager::LISTENER | HookManager::CONTROLLER | HookManager::RESULT);
	}
};