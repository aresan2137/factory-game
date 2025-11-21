#pragma once

#include "../define.h"

#include "Items.h"

class ChunkManager;

class Level {
public:

	Level();
	~Level();

	Vector2 playerPos = { 0.0f,0.0f };
	float playerSpeed = 600.0f;
	float zoom = 3.0f;

	ChunkManager* chunks;

	std::vector<unsigned short> item = { 200,20,20,20,100,330,21,90,230,10,99,101,20,0,0,0 };
	int hand[2] = {0,0};

private:

};