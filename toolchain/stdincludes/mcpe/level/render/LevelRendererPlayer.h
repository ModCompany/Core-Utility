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
    void updateDestroyProgress();

    void addTerrainParticleEffect(BlockPos const&,Block const&, Vec3 const&, float, float, float);
};

class BaseActorRenderer {
    public:
   // void extractRenderTextObjects(Tessellator &, stl::string const&, int, Vec3 const&, mce::Color const&, bool)
};