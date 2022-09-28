#pragma once

#include <vector>
#include <map>
#include <string>
#include <mod.h>
#include <jni.h>
#include <horizon/types.h>
class BlockSource;
#include <block/Block.h>

namespace DungeonUtility {
    class BlockData {
        public:
            BlockPos* pos;
            Block* block;
            Block* extra;
            BlockData(BlockPos*, Block*, Block*);

            virtual void setBlock(int const, int const, int const, BlockSource*) const;
    };

    class StructureObject {
        private:
            std::vector<BlockData*> blocks;
        public:
            std::vector<BlockData*>& getBlocks();
            void addBlock(BlockData*);
            void set(int const, int const, int const, BlockSource*) const;
    };

    struct LoadData {
        std::string text, name, type;
    };

    class StructurePool {
        private:
            static std::map<std::string, StructurePool*> pools;

            std::map<std::string, StructureObject*> structures;
        public:
            static std::map<StructurePool*, LoadData*> loads;
            StructurePool();
            void put(std::string, StructureObject*);
            StructureObject* get(std::string) const;

            bool isLoad(std::string) const;
            void deLoad(std::string);

            std::map<std::string, StructureObject*>& getStructures() const;
            std::vector<std::string> getAllStructure() const;
            void loadRuntime(std::string, std::string, std::string);
            void load(std::string, std::string, std::string);
            void copy(std::string, std::string);

            static void registerPool(std::string, StructurePool*);
            static StructurePool* getPool(std::string);
            static bool canPool(std::string);
    };

    class DungeonUtilityModule : public Module {
        public:
            DungeonUtilityModule();
            virtual void initialize();
    };

    class StructureParser {
        private:
            static std::map<std::string, StructureParser*> pasrsers;
        public:
            StructureParser();
            virtual std::string save(StructureObject*) const;
            virtual StructureObject* read(std::string const&) const;

            static void registerParser(std::string, StructureParser*);
            static StructureParser* getParserByName(std::string);
            static bool canParser(std::string);
    };

    class StructureJavaParser : public StructureParser {
        private:
            jobject self;
        public:
            static jclass parserClass;
            static jmethodID saveID, readID;


            StructureJavaParser(jobject);

            virtual std::string save(StructureObject*) const override;
            virtual StructureObject* read(std::string const&) const override;
    };
};