#pragma once

#include "../../define.h"

class TextureManager {
public:
	TextureManager();
	void init();

	uint LoadTextureFromFile(std::string filename);

	Texture2D GetTextureFromTID(uint TID);

	Texture2D GetTextureFromItemsAtlas(uint position);

	void SplitTextureAtlas(std::vector<Texture2D>& textures, const char* filePath);

private:
	std::vector<Texture2D> atlas;

	std::vector<Texture2D> textures;
	std::vector<std::string> filenames;
};

