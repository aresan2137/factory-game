#pragma once

#include "raylib.h"
#include "raymath.h"

#include <vector>
#include <iostream>
#include <string> 
#include <fstream>
#include <cstdint>

#define TexturePixels 8 // pixel count per element in texture atlas

#define ChunkSize 32 //max 256   

#define CoolingCooldown 10

#define TRANSGRAY { 130, 130, 130, 128 }

using byte = uint8_t;
using uint = uint32_t;

struct vec2int { int X, Y; };
struct ChunkObject {
	int cX, cY; // chunk positions
	int tX, tY; // tile positions
};

class Drawer;
class Level;
class Gui;
class TextureManager;
class Items;

extern Drawer drawer;
extern Level* currentLevel;
extern Gui gui;
extern TextureManager textures;
extern Items items;

/* TODO - LIST:
* ulepszyć culling w Drawer.cpp
* zrobić faktyczne generation list zamiast generować odrazu w ChuunkManager.cpp
* dodać multithreding
*/ 