//
// Created by zheka on 18/11/10.
//

#ifndef HORIZON_ITEM_H
#define HORIZON_ITEM_H

#include <stdlib.h>
#include <string.h>
#include <stl/vector>

template<typename _Tp>
using stl_vector = std::__ndk1::vector<_Tp>; 
class Actor;
class Mob;
class Player;
class ItemStackBase;
class ItemStack;
class ItemInstance;

class Block;



class Item {
	public:
	char filler[256];
	Item(stl::string const&, short);

	virtual void getIcon(ItemStackBase const&, int, bool) const;
	virtual void requiresInteract() const;
	virtual void setIcon(stl::string const&, int);
	virtual void buildDescriptionName(ItemStackBase const&) const;
	virtual void hurtActor(ItemStack&, Actor&, Mob&) const;
	virtual void use(ItemStack&, Player&) const;
	virtual void _useOn(ItemStack&, Actor&, BlockPos, unsigned char, float, float,float) const;
	virtual void releaseUsing(ItemStack&, Player*, int) const;

	//pickaxe
	virtual void mineBlock(ItemStack&, Block const&, int, int, int, Actor*) const;
	virtual void mineBlock(ItemInstance&, Block const&, int,int,int, Actor*) const;
	virtual void canDestroyInCreative() const;
	virtual void getDestroySpeed(ItemStackBase const&, Block const&) const;
	virtual void canDestroySpecial(Block const&) const;

	virtual void getMaxDamage() const;
	virtual void getAttackDamage() const;
	virtual void getEnchantSlot() const;
	virtual void getEnchantValue() const;

	bool isArmor() const;

	class Tier {
		public:
		int getUses() const;
		int getLevel() const;
		int getEnchantmentValue() const;
		int getAttackDamageBonus() const;
		float getSpeed() const;
		Tier(int,int,float,int,int);
	};
};

class DiggerItem : public Item {
	public:
	char filler[25];

	virtual void getAttackDamage() const;
	virtual void mineBlock(ItemStack&, Block const&, int, int,int, Actor*) const;
};
class PickaxeItem : public DiggerItem {
	public:

	PickaxeItem(stl::string const&, int, Item::Tier const&);

};

class ItemDescriptor {
    public:

};



class ItemStackBase {
	public:
	Item* item;
	int getId() const;
};
class ItemStack : public ItemStackBase {
    public:

};

class FishingRodItem : public Item {
public:
	virtual void isHandEquipped() const;
	virtual void requiresInteract() const;
	virtual void getEnchantSlot() const;
	virtual void getEnchantValue() const;
	virtual void use(ItemStack&, Player&) const;
	virtual void hurtActor(ItemStack&, Actor&, Mob&) const;
	virtual void mineBlock(ItemStack&, Block const&, int, int, int, Actor*) const;
	virtual void getInteractText(Player const&) const;
	virtual void getAnimationFrameFor(Mob*, bool, ItemStack const*, bool) const;
	virtual void getIcon(ItemStackBase const&, int, bool) const;
	virtual void setIcon(stl::string const&, int);
public:
    //Methods
    FishingRodItem(stl::string const&, int);
};//FishingRodItem

#endif //HORIZON_ITEM_H
