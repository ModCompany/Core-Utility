
#include <hook.h>
#include <mod.h>
#include <logger.h>
#include <symbol.h>
#include <innercore_callbacks.h>
#include <nativejs.h>
#include <vtable.h>
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
#include "../../shared_headers/JavaClass.h"
typedef int content_id_t;



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

class DoorBlock : public BlockLegacy {
	public:
	enum class DoorType : int {
		LEFT,
		RIGHT
	};
	DoorBlock(stl::string const&, int, Material const&, DoorBlock::DoorType);
	
};

class MyBlockFactory : public LegacyBlockRegistry::LegacyBlockFactoryBase {
    virtual void registerBlock();
	virtual void applyProperties(){
		this->block->addState(VanillaStates::DoorHingeBit);
		this->block->addState(VanillaStates::Direction);
		this->block->addState(VanillaStates::OpenBit);
		this->block->addState(VanillaStates::UpperBlockBit);
	}
};

class LadderBlock : public BlockLegacy {
	public:
	LadderBlock(stl::string const&, int);
};


class MyBlockProvider : public LegacyBlockRegistry::LegacyBlockProviderBase {
public:
    MyBlockFactory* factory;
 
    MyBlockProvider(MyBlockFactory* factory) : LegacyBlockRegistry::LegacyBlockProviderBase() {
        this->factory = factory;
		this->factory->props.renderLayer = 7;
		this->factory->props.renderType = 7;
    };
 
    virtual LegacyBlockRegistry::LegacyBlockFactoryBase* getFactory() {
        return this->factory;
    }
	virtual void patchVtable(void** a){
			
			if(a!=nullptr){
			Logger::debug("TEST","TEST");
			//a[getVtableOffset("_ZTV9DoorBlock","_ZNK9DoorBlock3useER6PlayerRK8BlockPosh")] = SYMBOL("mcpe","_ZNK9DoorBlock3useER6PlayerRK8BlockPosh");
			///a[getVtableOffset("_ZTV9DoorBlock","_ZNK9DoorBlock18isInteractiveBlockEv")] = SYMBOL("mcpe","_ZNK9DoorBlock18isInteractiveBlockEv");
			//a[getVtableOffset("_ZTV9DoorBlock","_ZNK9DoorBlock7onPlaceER11BlockSourceRK8BlockPos")] = SYMBOL("mcpe", "_ZNK9DoorBlock7onPlaceER11BlockSourceRK8BlockPos");

			//a[getVtableOffset("_ZTV9DoorBlock","_ZNK9DoorBlock11isDoorBlockEv")] = SYMBOL("mcpe", "_ZNK9DoorBlock11isDoorBlockEv");
			//a[getVtableOffset("_ZTV9DoorBlock","_ZNK9DoorBlock4tickER11BlockSourceRK8BlockPosR6Random")] = SYMBOL("mcpe", "_ZNK9DoorBlock4tickER11BlockSourceRK8BlockPosR6Random");
			//a[getVtableOffset("_ZTV9DoorBlock","_ZNK9DoorBlock21getVisualShapeInWorldERK5BlockR11BlockSourceRK8BlockPosR4AABBb")] = SYMBOL("mcpe", "_ZNK9DoorBlock21getVisualShapeInWorldERK5BlockR11BlockSourceRK8BlockPosR4AABBb");
			}
	}
	virtual void onBlockItemCreated(){

		//ItemRegistry::registerCustomItem<BowItem>(new BowProvider(this),IdConversion::staticToDynamic(id, IdConversion::ITEM), nameId);
	}
	
};
 
void MyBlockFactory::registerBlock() {
    if (id != 0) {
        BlockRegistry::registerCustomBlock<DoorBlock>(new MyBlockProvider(this), IdConversion::staticToDynamic(id, IdConversion::BLOCK), nameId, *props.getMaterial(),DoorBlock::DoorType::LEFT);
		//BlockRegistry::registerCustomBlock<DoorBlock>(new MyBlockProvider(this), IdConversion::staticToDynamic(id, IdConversion::BLOCK), nameId, *props.getMaterial(),DoorBlock::DoorType::RIGHT);
    }
}

JS_EXPORT(Test, registerBlock, "V(I)", (JNIEnv* env, int id){
	auto factory = new MyBlockFactory();
	factory->initParameters(id, "test_block_1");
	LegacyBlockRegistry::registerBlockFactory(factory);
	LegacyItemRegistry::addItemToCreative(id, 1, 0, nullptr);
	Logger::debug("test", "test block registered!");
});