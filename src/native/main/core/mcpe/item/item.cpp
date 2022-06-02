
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

#include <innercore/common.h>
#include <innercore/item_registry.h>
#include <innercore/legacy_item_registry.h>
#include <innercore/id_conversion_map.h>

#include <core/JavaClass.h>
#include <core/VtableHelper.h>
#include <core/OverridedName.h>

typedef int content_id_t;


#define ItemToStatic(ID)  return IdConversion::dynamicToStatic(ID, IdConversion::ITEM);
#define ItemToDynamic(ID) return IdConversion::staticToDynamic(ID, IdConversion::ITEM);



class RangedWeaponItem : public Item {
	public:
	virtual void releaseUsing(ItemStack&, Player*, int) const;
};

class BowItem : public RangedWeaponItem {
	public:
	BowItem(stl::string const&, int);
};

class BowFactory : public LegacyItemRegistry::LegacyItemFactoryBase {
	public:
	BowFactory() : LegacyItemRegistry::LegacyItemFactoryBase() {};
	virtual void registerItem();
};

class BowProvider : public LegacyItemRegistry::LegacyItemProviderBase {
	public:
	BowFactory* factory;
	BowProvider(BowFactory* factory) : LegacyItemRegistry::LegacyItemProviderBase() {
		this->factory = factory;
		factory->props.durability = 10;
	}

	virtual LegacyItemRegistry::LegacyItemFactoryBase* getFactory(){
		return this->factory;
	}
	virtual void setupVtable(void* a){
       // LegacyItemRegistry::LegacyItemProviderBase::setupVtable(a);
		//
	//	void** table = *(void***) a;
		void** table = (void**) a;


		if(this->factory->item!=nullptr){

			void** table = *(void***) factory->item;
			table[getVtableOffset("_ZTV7BowItem", "_ZNK16RangedWeaponItem3useER9ItemStackR6Player")] = SYMBOL("mcpe", "_ZNK16RangedWeaponItem3useER9ItemStackR6Player");
			table[getVtableOffset("_ZTV7BowItem", "_ZNK4Item6_useOnER9ItemStackR5Actor8BlockPoshfff")] = SYMBOL("mcpe", "_ZNK4Item6_useOnER9ItemStackR5Actor8BlockPoshfff");
			table[getVtableOffset("_ZTV7BowItem","_ZNK16RangedWeaponItem9mineBlockER9ItemStackRK5BlockiiiP5Actor")] = SYMBOL("mcpe","_ZNK16RangedWeaponItem9mineBlockER9ItemStackRK5BlockiiiP5Actor");
			table[getVtableOffset("_ZTV7BowItem","_ZNK16RangedWeaponItem12releaseUsingER9ItemStackP6Playeri")] = SYMBOL("mcpe", "_ZNK16RangedWeaponItem12releaseUsingER9ItemStackP6Playeri");

		}

	}
};

void BowFactory::registerItem(){
	if(id!=0){
		ItemRegistry::registerCustomItem<BowItem>(new BowProvider(this),IdConversion::staticToDynamic(id, IdConversion::ITEM), nameId);
	}
}
/*
JS_EXPORT(Test, registerBow, "V(I)", (JNIEnv* env,int id){
	BowFactory* factory = new BowFactory();
	factory->initParameters(id, "test_bow", "Test Bow", "stick", 0);
	LegacyItemRegistry::registerItemFactory(factory);
})
*/

class ShieldItem : public Item {
	public:
	ShieldItem(stl::string const&, int);
};

class ShieldFactory : public LegacyItemRegistry::LegacyItemFactoryBase {
	public:
	ShieldFactory() : LegacyItemRegistry::LegacyItemFactoryBase() {};
	virtual void registerItem();
};


class ShieldProvider : public LegacyItemRegistry::LegacyItemProviderBase {
	public:
	ShieldFactory* factory;
	ShieldProvider(ShieldFactory* factory) : LegacyItemRegistry::LegacyItemProviderBase() {
		this->factory = factory;
		factory->props.durability = 10;
	}

	virtual LegacyItemRegistry::LegacyItemFactoryBase* getFactory(){
		return this->factory;
	}
	virtual void setupVtable(void* a){
       // LegacyItemRegistry::LegacyItemProviderBase::setupVtable(a);
		void** table = (void**) a;
	}
};

void ShieldFactory::registerItem(){
	if(id!=0){
		ItemRegistry::registerCustomItem<ShieldItem>(new ShieldProvider(this),IdConversion::staticToDynamic(id, IdConversion::ITEM), nameId);
	}
}

class FishingFactory : public LegacyItemRegistry::LegacyItemFactoryBase {
	public:
	FishingFactory() : LegacyItemRegistry::LegacyItemFactoryBase() {};
	virtual void registerItem();
};

class FishingProvider : public LegacyItemRegistry::LegacyItemProviderBase {
	public:
	FishingFactory* factory;
	FishingProvider(FishingFactory* factory) : LegacyItemRegistry::LegacyItemProviderBase() {
		this->factory = factory;
	}

	virtual LegacyItemRegistry::LegacyItemFactoryBase* getFactory(){
		return this->factory;
	}

	virtual void setupVtable(void* a){
		//LegacyItemRegistry::LegacyItemProviderBase::setupVtable(a);
		void** table = (void**) a;
		//table[getVtableOffset("_ZTV14FishingRodItem", "_ZNK14FishingRodItem3useER9ItemStackR6Player")] = SYMBOL("mcpe", "_ZNK14FishingRodItem3useER9ItemStackR6Player");
		//table[getVtableOffset("_ZTV14FishingRodItem", "_ZNK4Item6_useOnER9ItemStackR5Actor8BlockPoshfff")] = SYMBOL("mcpe", "_ZNK4Item6_useOnER9ItemStackR5Actor8BlockPoshfff");
		//table[getVtableOffset("_ZTV14FishingRodItem", "_ZNK4Item20validFishInteractionEi")] = SYMBOL("mcpe", "_ZNK4Item20validFishInteractionEi");
		//table[getVtableOffset("_ZTV14FishingRodItem", "_ZNK14FishingRodItem16requiresInteractEv")] = SYMBOL("mcpe", "_ZNK14FishingRodItem16requiresInteractEv");
	}
};

void FishingFactory::registerItem(){
	if(id!=0){
		ItemRegistry::registerCustomItem<FishingRodItem>(new FishingProvider(this),IdConversion::staticToDynamic(id, IdConversion::ITEM), nameId);
	}
}
#include <stl/vector>

class MobEffectInstance {
public:
	char filler[28];
	MobEffectInstance(unsigned int potionId, int duration, int amplifier, bool isAmbient, bool alwaysTrue, bool textureSomething);

};

class ArrowItem : public Item {
	public:
	char filler[256];
	ArrowItem(stl::string const&, int);
	stl::vector<MobEffectInstance> getMobEffects(int) const {
		stl::vector<MobEffectInstance> vector;
		vector.push_back(MobEffectInstance(5,20*2,2,true,true,true));
		Logger::debug("ArrowItem", "Debug");
		Logger::flush();
		return vector;
	};
};

class ArrowFactory : public LegacyItemRegistry::LegacyItemFactoryBase {
	public:
	ArrowFactory() : LegacyItemRegistry::LegacyItemFactoryBase() {};
	virtual void registerItem();
};

class ArrowProvider : public LegacyItemRegistry::LegacyItemProviderBase {
	public:
	ArrowFactory* factory;
	ArrowProvider(ArrowFactory* factory) : LegacyItemRegistry::LegacyItemProviderBase() {
		this->factory = factory;
	}

	virtual LegacyItemRegistry::LegacyItemFactoryBase* getFactory(){
		return this->factory;
	}


	virtual void setupVtable(void* a){
		//LegacyItemRegistry::LegacyItemProviderBase::setupVtable(a);
		void** table = (void**) a;
		//table[getVtableOffset("_ZTV9ArrowItem", "_ZNK9ArrowItem13getMobEffectsEi")] = (void*) &ArrowProvider::getEffects;
		//table[getVtableOffset("_ZTV14FishingRodItem", "_ZNK4Item6_useOnER9ItemStackR5Actor8BlockPoshfff")] = SYMBOL("mcpe", "_ZNK4Item6_useOnER9ItemStackR5Actor8BlockPoshfff");
		//table[getVtableOffset("_ZTV14FishingRodItem", "_ZNK4Item20validFishInteractionEi")] = SYMBOL("mcpe", "_ZNK4Item20validFishInteractionEi");
		//table[getVtableOffset("_ZTV14FishingRodItem", "_ZNK14FishingRodItem16requiresInteractEv")] = SYMBOL("mcpe", "_ZNK14FishingRodItem16requiresInteractEv");
	}
};

void ArrowFactory::registerItem(){
	if(id!=0){
		ItemRegistry::registerCustomItem<ArrowItem>(new ArrowProvider(this),IdConversion::staticToDynamic(id, IdConversion::ITEM), nameId);
	}
}

JS_MODULE_VERSION(TestItem, 1);
JS_EXPORT(TestItem, reg, "V(I)", (JNIEnv* env, int a){
	ArrowFactory* factory = new ArrowFactory();
	factory->initParameters(a, "test_item", "arrow", "stick",0);

	LegacyItemRegistry::registerItemFactory(factory);
});






stl::string getName(Item* item,ItemStackBase const& stack){
	int id = IdConversion::dynamicToStatic(stack.getId(), IdConversion::ITEM);
	return OverridedName::getNameForId(id,stack.getAuxValue());
};

int getAttackDamage(Item* item){
	
	return 40;
}

export(void, Item_overrideName, int id,int data, jstring name){
	Item* item = ItemRegistry::getItemById(IdConversion::staticToDynamic(id, IdConversion::ITEM));
	if(item){
		const char* a = JavaClass::release(env, name);
        OverridedName::addNameForId(id,data, a);
		VtablePatcher patcher(VtableCache::VtableType::ITEM,id,item);
		patcher.patch("_ZTV4Item", "_ZNK4Item20buildDescriptionNameERK13ItemStackBase",(void*) &getName);
	}
}

export(void, Item_overrideArmorValue, int id){
	Item* item = ItemRegistry::getItemById(IdConversion::staticToDynamic(id, IdConversion::ITEM));
	if(item){
		VtableHelper helper (item);
		helper.resize();
		helper.patch("_ZTV4Item", "_ZNK4Item13getArmorValueEv",(void*) &getAttackDamage);
	}
}

#include <core/JniInjector.h>
#include <innercore/global_context.h>
