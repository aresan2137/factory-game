#include "Drawer.h"

#include "../define.h"

#include "Chunk.h"
#include "Level.h"
#include "Managers/Buildings/Building.h"
#include "Managers/ChunkManager.h"
#include "Managers/TextureManager.h"

Drawer::Drawer() {}
void Drawer::init() {

    cullingChunks.resize(12);
    cullingVEC2.resize(12);

    player = LoadTexture("resources/player.png");
    textures.SplitTextureAtlas(ground,"resources/ground.png");
}

void Drawer::DrawGame() {

    UpdateCulling();

    for (int i = 0; i < cullingChunks.size(); i++) {
        if (cullingChunks[i] != nullptr) {
            DrawChunk(cullingChunks[i]);
        }
    }
    
	DrawTextureEx(player, Vector2SubtractValue({ screensize.x / 2, screensize.y / 2 }, currentLevel->zoom * 8), 0.0f, currentLevel->zoom * 2, WHITE);
}

void Drawer::DrawChunk(Chunk* chunk) {
    Vector2 Start = chunk->GetChunkPixelPos();
    Vector2 TexPos = Start;

    for (int i = 0; i < ChunkSize; i++) {
        for (int j = 0; j < ChunkSize; j++) {
            DrawTextureEx(ground[chunk->ground[i][j]], TexPos, 0.0f, currentLevel->zoom, WHITE);
            TexPos.x += TexturePixels * currentLevel->zoom;
        }
        TexPos.y += TexturePixels * currentLevel->zoom;
        TexPos.x = Start.x;
    }

    for (int i = 0; i < chunk->buildings.size(); i++) {
        Vector2 pos = Vector2Add(Vector2Scale({ (float)chunk->buildings[i]->pos.X,(float)chunk->buildings[i]->pos.Y }, TexturePixels * currentLevel->zoom), Start);
        chunk->buildings[i]->Draw(pos);
    }

}

void Drawer::UpdateCulling() {
    if (cullingCooldown < 0) {
        cullingCooldown = CoolingCooldown;

        float basemul2 = TexturePixels * ChunkSize;
        Vector2 playerpose = Vector2Divide(currentLevel->playerPos, { basemul2,basemul2 });
        playerpose.x = ceil(playerpose.x);
        playerpose.y = ceil(playerpose.y);

        int gg = 0;
        for (int ir = -2; ir < 4; ir++) {
            for (int jr = -1; jr < 3; jr++) {
                int io = ir - playerpose.x;
                int jo = jr - playerpose.y;
                if (gg >= cullingVEC2.size()) cullingVEC2.resize(gg+1);
                cullingVEC2[gg] = { { io,jo }, true };
                gg++;
            }
        }

        if (cullingVEC2.size() != cullingChunks.size()) cullingChunks.resize(cullingVEC2.size());

        for (int i = 0; i < cullingVEC2.size(); i++) {
            if (!cullingVEC2[i].second) {
                cullingChunks[i] = nullptr;
                continue;
            }

            cullingChunks[i] = currentLevel->chunks->GetChunk(cullingVEC2[i].first);
            if (cullingChunks[i] == nullptr) {
                cullingCooldown = 0;
                currentLevel->chunks->AddChunkToGenerationLine(cullingVEC2[i].first);
            }
        }
    }
    cullingCooldown--;
}