
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


typedef int content_id_t;

#define ItemToStatic(ID) return IdConversion::dynamicToStatic(ID, IdConversion::ITEM);
#define ItemToDynamic(ID) return IdConversion::staticToDynamic(ID, IdConversion::ITEM);

void BowFactory::registerItem()
{
	if (id != 0)
	{
		ItemRegistry::registerCustomItem<BowItem>(new BowProvider(this), IdConversion::staticToDynamic(id, IdConversion::ITEM), nameId);
	}
}

void ShieldFactory::registerItem()
{
	if (id != 0)
	{
		ItemRegistry::registerCustomItem<ShieldItem>(new ShieldProvider(this), IdConversion::staticToDynamic(id, IdConversion::ITEM), nameId);
	}
}

void FishingFactory::registerItem(){
	if (id != 0){
		ItemRegistry::registerCustomItem<FishingRodItem>(new FishingProvider(this), IdConversion::staticToDynamic(id, IdConversion::ITEM), nameId);
	}
}

void DoorItemFactory::registerItem(){
	if (id != 0){
		ItemRegistry::registerCustomItem<DoorItem>(new DoorItemProvider(this), IdConversion::staticToDynamic(id, IdConversion::ITEM), nameId,DoorBlock::DoorType::Oak);
	}
}

stl::string getName(Item *item, ItemStackBase const &stack)
{
	int id = IdConversion::dynamicToStatic(stack.getId(), IdConversion::ITEM);
	return OverridedItem::OverridedName::getNameForId(id, stack.getAuxValue());
};

int getAttackDamage(Item *item)
{
	short id = IdConversion::dynamicToStatic(item->getId(), IdConversion::ITEM);
	return OverridedItem::OverridedArmor::getArmorForId(id);
};


export(void, mcpe_item_Item_overrideName, int id, int data, jstring name)
{
	Item *item = ItemRegistry::getItemById(IdConversion::staticToDynamic(id, IdConversion::ITEM));
	if (item)
	{
		const char *a = JavaClass::release(env, name);
		OverridedItem::OverridedName::addNameForId(id, data, a);
		VtablePatcher patcher(VtableCache::VtableType::ITEM, id, item);
		patcher.patch("_ZTV4Item", "_ZNK4Item20buildDescriptionNameERK13ItemStackBase", (void *)&getName);
	}
}

export(void, mcpe_item_Item_overrideArmorValue, int id, float value)
{
	Item *item = ItemRegistry::getItemById(IdConversion::staticToDynamic(id, IdConversion::ITEM));
	if (item)
	{
		OverridedItem::OverridedArmor::addArmorForId(id, value);
		VtablePatcher patcher(VtableCache::VtableType::ITEM, id, item);
		patcher.patch("_ZTV4Item", "_ZNK4Item13getArmorValueEv", (void *)&getAttackDamage);
	}
}


#include <core/JniInjector.h>
#include <innercore/global_context.h>
