#pragma once

#include "../../define.h"

class Chunk;

class ChunkManager {
public:
	ChunkManager();
	~ChunkManager();

	Chunk* GetChunk(vec2int Pos);

	void AddChunkToGenerationLine(vec2int Pos);

	ChunkObject GetPixelPosChunkObject(Vector2 screenPos);

	void Tick();


private:

	std::vector<vec2int> generationLine;

	std::vector<std::vector<Chunk*>> chunks_2_1;
	std::vector<std::vector<Chunk*>> chunks_2_2;
	std::vector<std::vector<Chunk*>> chunks_2_3;
	std::vector<std::vector<Chunk*>> chunks_2_4;

	std::vector<Chunk*> chunks_1_1;
	std::vector<Chunk*> chunks_1_2;
	std::vector<Chunk*> chunks_1_3;
	std::vector<Chunk*> chunks_1_4;

	Chunk* chunks_0_1;

};
