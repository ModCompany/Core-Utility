#pragma once

#include <api/HashedString.h>
#include <stl/string>
#define stl std::__ndk1


class BlockPos;
class ItemState;
class BlockSource;
class Random;
class BlockSupportType;
class Material {};

class VanillaStates {
	public:
	static ItemState DoorHingeBit;
	static ItemState DirtType;
	static ItemState UpperBlockBit;
	static ItemState Direction;
	static ItemState OpenBit;
};

class AABB;
class Player;
class Actor;

class BlockLegacy {
public:
    char filler[0xA18u];  
    BlockLegacy(stl_string const&, int, Material const&);
	void addState(ItemState const&);
	virtual void getNextBlockPermutation(Block const&) const;
	virtual void getAABB(BlockSource&, BlockPos const&, Block const&, AABB&, bool) const;
	virtual void getLiquidClipVolume(BlockSource&, BlockPos const&, AABB&) const;
	virtual void isDoorBlock() const;
	virtual void canFillAtPos(BlockSource&, BlockPos const&, Block const&) const;
	virtual void onFillBlock(BlockSource&, BlockPos const&, Block const&) const;
	virtual void checkIsPathable(Actor&, BlockPos const&, BlockPos const&) const;
	virtual void onRedstoneUpdate(BlockSource&, BlockPos const&, int, bool) const;
	virtual void setupRedstoneComponent(BlockSource&, BlockPos const&) const;
	virtual void mayPlace(BlockSource&, BlockPos const&) const;
	virtual void neighborChanged(BlockSource&, BlockPos const&, BlockPos const&) const;
	virtual void getSecondPart(BlockSource&, BlockPos const&, BlockPos&) const;
	virtual void getResourceCount(Random&, Block const&, int, bool) const;
	virtual void getResourceItem(Random&, Block const&, int) const;
	virtual void asItemInstance(BlockSource&, BlockPos const&, Block const&) const;
	virtual void getVisualShapeInWorld(Block const&, BlockSource&, BlockPos const&, AABB&, bool) const;
	virtual void getVariant(Block const&) const;
	virtual void canBeSilkTouched() const;
	virtual void getSilkTouchItemInstance(Block const&) const;
	virtual void onPlace(BlockSource&, BlockPos const&) const;
	virtual void tick(BlockSource&, BlockPos const&, Random&) const;
	virtual void isInteractiveBlock() const;
	virtual void use(Player&, BlockPos const&, unsigned char) const;
	virtual void canSurvive(BlockSource&, BlockPos const&) const;
	public:

};

class DoorBlock : public BlockLegacy {
	public:
	char filler[104];
	short id;
	enum class DoorType : int {
		Oak,
        Spruce,
        Birch,
        Jungle,
        Acacia,
        Dark_Oak,
        Iron,
        Crimson,
        Warped
	};
	DoorBlock(stl::string const&, int, Material const&, DoorBlock::DoorType);
	void _hasSupport(BlockPos const&, unsigned char, BlockSupportType, BlockSource&) const;
    void hasRightHinge(BlockSource&, BlockPos const&) const;
    void getDoorFacing(int);
    void stringToDoorType(stl::string);
    void shouldFlipTexture(BlockSource&, BlockPos const&, unsigned char) const;
    void getDoorPosition(BlockSource&, BlockPos const&, BlockPos&, BlockPos&) const;
    void getDoorThickness() const;
    void setToggled(BlockSource&, BlockPos const&, bool) const;
    void isToggled(BlockSource&, BlockPos const&) const;
    void getBlockedDirection(BlockSource&, BlockPos const&) const;
    void getDoorBlocks(BlockSource&, BlockPos const&, Block const*&, Block const*&) const;
    void getDir(BlockSource&, BlockPos const&) const;
    void _isDoorComplete(BlockSource const&, BlockPos const&);
};
