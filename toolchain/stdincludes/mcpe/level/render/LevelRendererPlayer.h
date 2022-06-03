#pragma once


class BlockPos;
class LevelRendererPlayer;
class LevelRenderer {
    public:
    LevelRendererPlayer* getLevelRendererPlayer();
};

class LevelRendererPlayer {
    public:
    void addDestroyBlock(BlockPos const&, float);
};