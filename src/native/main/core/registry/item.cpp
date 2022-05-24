
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

JS_MODULE_VERSION(TestItem, 1);
JS_EXPORT(TestItem, reg, "V(I)", (JNIEnv* env, int a){
	FishingFactory* factory = new FishingFactory();
	factory->initParameters(a, "test_item", "Ydo4ka", "stick",0);
	factory->props.durability = 100;
	LegacyItemRegistry::registerItemFactory(factory);
});


template<typename A, typename ... B> class FabricItem : public LegacyItemRegistry::LegacyItemFactoryBase{
	public:
	FabricItem() : LegacyItemRegistry::LegacyItemFactoryBase() {

	};

	virtual void registerItem(B...b);

};

template<typename A,typename ...B> class FabricItemProvider : public LegacyItemRegistry::LegacyItemProviderBase  {
	public:
	FabricItem<A>* factory;
	FabricItemProvider(FabricItem<A>* a){
		this->factory = a;
	}

	virtual LegacyItemRegistry::LegacyItemFactoryBase* getFactory() {
		return this->factory;
	}


};

template<typename A, typename ... B> void FabricItem<A,B...>::registerItem(B...b){
	Logger::debug("Test", "TEst");
	Logger::flush();
	ItemRegistry::registerCustomItem<A>(new FabricItem<A>(this),IdConversion::staticToDynamic(id, IdConversion::ITEM), nameId, b...);
}



template<typename T>
class LegacyItemRegistryWrapper {
	public:
	class LegacyItemRegistryWrapperFactory : public LegacyItemRegistry::LegacyItemFactoryBase {
		public:
		LegacyItemRegistryWrapper *wrapper;

		LegacyItemRegistryWrapperFactory() : LegacyItemRegistry::LegacyItemFactoryBase() {};

		void registerItem() override {
		wrapper->registerItem();
		};
		};

	LegacyItemRegistryWrapperFactory *registryWrapperFactory;

	class LegacyItemRegistryWrapperProvider : public LegacyItemRegistry::LegacyItemProviderBase {
		public:
		LegacyItemRegistryWrapperFactory *factory;
		LegacyItemRegistryWrapper *wrapper;

		explicit LegacyItemRegistryWrapperProvider(LegacyItemRegistryWrapperFactory *factory)
		: LegacyItemRegistry::LegacyItemProviderBase() {

		this->factory = factory;
		}

		LegacyItemRegistry::LegacyItemFactoryBase *getFactory() override {
		return this->factory;
		}


	};

	virtual void registerItem() {
		auto provider = new LegacyItemRegistryWrapperProvider(registryWrapperFactory);
		provider->wrapper = this;
		ItemRegistry::registerCustomItem<T>(provider,
		IdConversion::staticToDynamic(registryWrapperFactory->id,
		IdConversion::ITEM),registryWrapperFactory->nameId);
		Logger::debug("Test","TEEST");
		Logger::flush();
	};


	void registerWrapper() {
		auto factory = new LegacyItemRegistryWrapperFactory();
		factory->wrapper = this;

	}
};

class TestItem : public LegacyItemRegistryWrapper<Item> {
	public:
	TestItem() : LegacyItemRegistryWrapper<Item>() {

	}
};

namespace ItemWrapper {
	template<class A,class ... B>
	class ItemWrappedFactory : public LegacyItemRegistry::LegacyItemFactoryBase {
		public:

		ItemWrappedFactory() : LegacyItemRegistry::LegacyItemFactoryBase() {

		}

		virtual void registerItem(B...b) override;
		virtual void setupVtable(void* a);
	};

	template<class A, class ... B>
	class ItemWrappedProvider : public LegacyItemRegistry::LegacyItemProviderBase {
		public:
		ItemWrappedFactory<A,B...>* factory;

		ItemWrappedProvider(ItemWrappedFactory<A,B...>* a) : LegacyItemRegistry::LegacyItemProviderBase(){
			this->factory = a;
		};
		virtual LegacyItemRegistry::LegacyItemFactoryBase* getFactory(){
			return this->factory;
		}
	};


}

template<class A,class ...B> void ItemWrapper::ItemWrappedFactory<A,B...>::registerItem(B...args){
	if(id != 0){
		ItemRegistry::registerCustomItem<A>(new ItemWrappedProvider<A,B...>(this), IdConversion::staticToDynamic(id, IdConversion::ITEM), nameId,args...);
	}
}




stl::string getName(Item* item,ItemStackBase const& stack){
	int id = IdConversion::dynamicToStatic(stack.getId(), IdConversion::ITEM);
	return OverridedName::getNameForId(id);
};

int getAttackDamage(Item* item){
	
	return 40;
}

export(void, Item_overrideName, int id, jstring name){
	Item* item = ItemRegistry::getItemById(IdConversion::staticToDynamic(id, IdConversion::ITEM));
	if(item){
		const char* a = env->GetStringUTFChars(name, NULL);
        OverridedName::addNameForId(id, a);
		env->ReleaseStringUTFChars(name, a);
		VtableHelper helper (item);
		helper.resize();
		helper.patch("_ZTV4Item", "_ZNK4Item20buildDescriptionNameERK13ItemStackBase",(void*) &getName);
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