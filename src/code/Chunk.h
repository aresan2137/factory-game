#pragma once

#include "../define.h"

class Building;

class Chunk
{
public:

	Chunk(int X, int Y);

	Vector2 GetChunkPixelPos();
	
	byte ground[ChunkSize][ChunkSize];

	short X, Y;

	std::vector<Building*> buildings;
private:

};