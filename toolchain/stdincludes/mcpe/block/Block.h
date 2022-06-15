#pragma once

#include <stl/string>
#define stl std::__ndk1
#include <innercore/legacy_block_registry.h>

class BushBlock : public BlockLegacy {
    public:
    char filler[256];

};

class CropBlock : public BushBlock {
    public:
    char filler[256];

    CropBlock(stl::string const&, int);
    int getGrowthSpeed(BlockSource&, BlockPos const&) const;
};

class CustomCropBlock : public CropBlock {
    public:
    char filler[256];

    CustomCropBlock(stl::string const& name, int itemid) : CropBlock(name,itemid) { 

    }

};



template<typename T>
class BlockRegistryWrapper {
    public:
        class BlockRegistryWrapperFactory : public LegacyBlockRegistry::LegacyBlockFactoryBase {
        public:
        BlockRegistryWrapper *wrapper;
        BlockRegistryWrapperFactory() : LegacyBlockRegistry::LegacyBlockFactoryBase() {};
        void registerBlock() override {
            wrapper->registerBlock();
        };
    };

    BlockRegistryWrapperFactory *registryWrapperFactory;
        class BlockRegistryWrapperProvider : public LegacyBlockRegistry::LegacyBlockProviderBase {
            public:
            BlockRegistryWrapperFactory *factory;
            BlockRegistryWrapper *wrapper;

        explicit BlockRegistryWrapperProvider(BlockRegistryWrapperFactory *factory) : LegacyBlockRegistry::LegacyBlockProviderBase() {
            this->factory = factory;
        }

        LegacyBlockRegistry::LegacyBlockProviderBase *getFactory() override {
            return this->factory;
        }

        void setupVtable(void *a) override {
            wrapper->setupVtable(a);
        }
    };

    virtual void registerBlock() {
        auto provider = new BlockRegistryWrapperProvider(registryWrapperFactory);
        provider->wrapper = this;
        if (registryWrapperFactory->id != 0) {
            BlockRegistry::registerCustomBlock<T>(provider,IdConversion::staticToDynamic(registryWrapperFactory->id, IdConversion::BLOCK), registryWrapperFactory->nameId, *registryWrapperFactory->props.getMaterial());
        }
    };

    virtual void setupVtable(void *a) = 0;

    void registerWrapper() {
        auto factory = new BlockRegistryWrapperFactory();
        factory->wrapper = this;
        factory->registerBlock();
    }
};