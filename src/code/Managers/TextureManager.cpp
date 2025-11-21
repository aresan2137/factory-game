#include "TextureManager.h"

#include "../../define.h"

TextureManager::TextureManager() {}
void TextureManager::init() {
    SplitTextureAtlas(atlas, "resources/build/items.png");
}

uint TextureManager::LoadTextureFromFile(std::string filename) {
    for (int i = 0; i < filenames.size(); i++) {
        if (filenames[i] == filename) return i;
    }
    filenames.push_back(filename);
    textures.push_back(LoadTexture(filename.c_str()));
    return filenames.size() - 1;
}

Texture2D TextureManager::GetTextureFromTID(uint TID) {
#ifndef NDEBUG
    if (TID >= textures.size()) {
        std::cout << "ERROR: GetTextureFromTID() -> invalid position\n";
        abort();
    }
#endif 
    return textures[TID];
}

Texture2D TextureManager::GetTextureFromItemsAtlas(uint position) {
#ifndef NDEBUG
    if (position >= atlas.size()) {
        std::cout << "ERROR: GetTextureFromAtlas() -> invalid position\n";
        abort();
    }
#endif 
    return atlas[position];
}

void TextureManager::SplitTextureAtlas(std::vector<Texture2D>& textures, const char* filePath) {
    
    Image blocksAtlas = LoadImage(filePath);

    textures.resize(blocksAtlas.height / TexturePixels * blocksAtlas.width / TexturePixels);

    int rep = 0;
    for (float x = 0; x < blocksAtlas.height / TexturePixels; x++) {
        for (float y = 0; y < blocksAtlas.width / TexturePixels; y++) {
            Rectangle srcRecGrass = { y * TexturePixels, x * TexturePixels, TexturePixels, TexturePixels };
            Image tempImage = ImageFromImage(blocksAtlas, srcRecGrass);
            textures[rep] = LoadTextureFromImage(tempImage);
            UnloadImage(tempImage);
            rep++;
        }
    }
}

