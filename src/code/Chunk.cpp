#include "Chunk.h"

#include "../define.h"

#include "Level.h"
#include "Drawer.h"

Chunk::Chunk(int X, int Y) 
	: X(X) 
	, Y(Y) {
	Image perlin1 = GenImagePerlinNoise(ChunkSize, ChunkSize, Y * ChunkSize, X * ChunkSize, 0.35f);
	Image perlin2 = GenImagePerlinNoise(ChunkSize, ChunkSize, Y * ChunkSize, X * ChunkSize, 1.0f);

	
	for (int i = 0; i < ChunkSize; i++) {
		for (int j = 0; j < ChunkSize; j++) {
			float wyn = ((GetImageColor(perlin1, i, j).r * 2.0f) + (GetImageColor(perlin2, i, j).r * 0.5f)) / (255.0f * 2.0f);
			if (wyn > 0.6) {
				ground[i][j] = 2;
			} else if (wyn > 0.55) {
				ground[i][j] = 1;
			} else {
				ground[i][j] = 0;
			}

			if (i == 0 && j == 0 || i == ChunkSize - 1 && j == 0 || i == 0 && j == ChunkSize - 1 || i == ChunkSize - 1 && j == ChunkSize - 1) ground[i][j] = 3;
		}
	}

	UnloadImage(perlin1);
	UnloadImage(perlin2);
}

Vector2 Chunk::GetChunkPixelPos() {
	float chunkPixelSize = TexturePixels * ChunkSize;

	float worldX = X * chunkPixelSize;
	float worldY = Y * chunkPixelSize;

	float screenX = drawer.screensize.x / 2 + (worldX + currentLevel->playerPos.x) * currentLevel->zoom;
	float screenY = drawer.screensize.y / 2 + (worldY + currentLevel->playerPos.y) * currentLevel->zoom;

	return { screenX, screenY };
} 