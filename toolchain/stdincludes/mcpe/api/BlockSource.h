#pragma once

class Block;
class BlockPos;

class BlockSource {
    public:
        bool hasBlock(int, int, int);
        bool isEmptyBlock(int, int, int);
        Block const& getBlock(int, int, int) const;
        void setBlock(int, int, int, Block const&, int);
        void setExtraBlock(BlockPos const&, Block const&, int);
        void updateNeighborsAt(BlockPos const&);
        void neighborChanged(BlockPos const&, BlockPos const&);
        void setBlockNoUpdate(int, int, int, Block const&);
        void setBlockNoUpdate(BlockPos const&, Block const&);
        void fireAreaChanged(BlockPos const&, BlockPos const&);
        void getTopBlock(int, int&, int);
        void addToTickingQueue(BlockPos const&, Block const&, int, int);
};

class BlockSourceProvider {
    public:
        void setBlock(int, int, int, Block const&);
        void setAllowBlockUpdate(bool);
        void setBlockUpdateType(int);
        void setCustomBlockSource(BlockSource*);
};