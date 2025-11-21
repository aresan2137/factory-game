#pragma once

#include "../define.h"

class Chunk;

class Drawer
{
public:
	Drawer();
	void init();

	void DrawGame();
	

	Vector2 screensize;

private:

	void DrawChunk(Chunk* chunk);

	void UpdateCulling();

	int cullingCooldown = 0;

	std::vector<Chunk*> cullingChunks;
	std::vector<std::pair<vec2int,bool>> cullingVEC2;

	Texture2D player;
	std::vector<Texture2D> ground;

};