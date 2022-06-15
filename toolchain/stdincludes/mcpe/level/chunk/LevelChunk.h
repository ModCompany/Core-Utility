#pragma once

class Biome;
class ChunkBlockPos;
class ChunkPos;

class LevelChunk {
	public:
	int getMin() const;
	int getMax() const;
    void setBiome(Biome const&,ChunkBlockPos const&);
    void setGrassColor(int,ChunkBlockPos const&);
	Biome* getBiome(ChunkBlockPos const&) const;
    ChunkPos const& getPosition()const;
};
