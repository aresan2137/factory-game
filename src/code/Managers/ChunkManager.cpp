#include "ChunkManager.h"

#include "../Chunk.h"
#include "../Drawer.h"
#include "../Level.h"
#include "Buildings/BuildingManager.h"
#include "../Gui.h"
#include "Buildings/Building.h"

ChunkManager::ChunkManager() {
	chunks_0_1 = new Chunk(0,0);
}

ChunkManager::~ChunkManager() {

}

Chunk* ChunkManager::GetChunk(vec2int Pos) { // KOD CHATGPT MOŻE NIEDZAŁAĆ

    if (Pos.X == 0 && Pos.Y == 0) return chunks_0_1;

    if (Pos.X == 0) {
        if (Pos.Y > 0) return Pos.Y < chunks_1_1.size() ? chunks_1_1[Pos.Y] : nullptr;
        else return -Pos.Y < chunks_1_2.size() ? chunks_1_2[-Pos.Y] : nullptr;
    }
    if (Pos.Y == 0) {
        if (Pos.X > 0) return Pos.X < chunks_1_3.size() ? chunks_1_3[Pos.X] : nullptr;
        else return -Pos.X < chunks_1_4.size() ? chunks_1_4[-Pos.X] : nullptr;
    }

    if (Pos.X > 0 && Pos.Y > 0)
        return (Pos.X < chunks_2_1.size() && Pos.Y < chunks_2_1[Pos.X].size()) ? chunks_2_1[Pos.X][Pos.Y] : nullptr;
    else if (Pos.X < 0 && Pos.Y > 0)
        return (-Pos.X < chunks_2_2.size() && Pos.Y < chunks_2_2[-Pos.X].size()) ? chunks_2_2[-Pos.X][Pos.Y] : nullptr;
    else if (Pos.X < 0 && Pos.Y < 0)
        return (-Pos.X < chunks_2_3.size() && -Pos.Y < chunks_2_3[-Pos.X].size()) ? chunks_2_3[-Pos.X][-Pos.Y] : nullptr;
    else
        return (Pos.X < chunks_2_4.size() && -Pos.Y < chunks_2_4[Pos.X].size()) ? chunks_2_4[Pos.X][-Pos.Y] : nullptr;

    return nullptr;
}

void ChunkManager::AddChunkToGenerationLine(vec2int Pos) {
    Chunk* chunk = new Chunk(Pos.X, Pos.Y);

    // (0,0)
    if (Pos.X == 0 && Pos.Y == 0) {
        chunks_0_1 = chunk;
        return;
    }

    // X = 0, Y != 0
    if (Pos.X == 0) {
        if (Pos.Y > 0) {
            if (Pos.Y >= chunks_1_1.size())
                chunks_1_1.resize(Pos.Y + 1, nullptr);
            chunks_1_1[Pos.Y] = chunk;
        } else {
            int idx = -Pos.Y;
            if (idx >= chunks_1_2.size())
                chunks_1_2.resize(idx + 1, nullptr);
            chunks_1_2[idx] = chunk;
        }
        return;
    }

    // Y = 0, X != 0
    if (Pos.Y == 0) {
        if (Pos.X > 0) {
            if (Pos.X >= chunks_1_3.size())
                chunks_1_3.resize(Pos.X + 1, nullptr);
            chunks_1_3[Pos.X] = chunk;
        } else {
            int idx = -Pos.X;
            if (idx >= chunks_1_4.size())
                chunks_1_4.resize(idx + 1, nullptr);
            chunks_1_4[idx] = chunk;
        }
        return;
    }

    // X != 0, Y != 0 (ćwiartki)
    if (Pos.X > 0 && Pos.Y > 0) {
        if (Pos.X >= chunks_2_1.size())
            chunks_2_1.resize(Pos.X + 1);
        if (Pos.Y >= chunks_2_1[Pos.X].size())
            chunks_2_1[Pos.X].resize(Pos.Y + 1, nullptr);
        chunks_2_1[Pos.X][Pos.Y] = chunk;
    } else if (Pos.X < 0 && Pos.Y > 0) {
        int x = -Pos.X;
        if (x >= chunks_2_2.size())
            chunks_2_2.resize(x + 1);
        if (Pos.Y >= chunks_2_2[x].size())
            chunks_2_2[x].resize(Pos.Y + 1, nullptr);
        chunks_2_2[x][Pos.Y] = chunk;
    } else if (Pos.X < 0 && Pos.Y < 0) {
        int x = -Pos.X, y = -Pos.Y;
        if (x >= chunks_2_3.size())
            chunks_2_3.resize(x + 1);
        if (y >= chunks_2_3[x].size())
            chunks_2_3[x].resize(y + 1, nullptr);
        chunks_2_3[x][y] = chunk;
    } else { // Pos.X > 0 && Pos.Y < 0
        int y = -Pos.Y;
        if (Pos.X >= chunks_2_4.size())
            chunks_2_4.resize(Pos.X + 1);
        if (y >= chunks_2_4[Pos.X].size())
            chunks_2_4[Pos.X].resize(y + 1, nullptr);
        chunks_2_4[Pos.X][y] = chunk;
    }
}

void ChunkManager::Tick() {
    float delta = GetFrameTime();
    for (int i = 0; i < chunks_2_1.size(); i++) {
        for (int j = 0; j < chunks_2_1[i].size(); j++) {
            if (chunks_2_1[i][j] != nullptr)
            for (int k = 0; k < chunks_2_1[i][j]->buildings.size(); k++) {
                chunks_2_1[i][j]->buildings[k]->Tick(delta);
            }
        }
    }
    for (int i = 0; i < chunks_2_2.size(); i++) {
        for (int j = 0; j < chunks_2_2[i].size(); j++) {
            if (chunks_2_2[i][j] != nullptr)
            for (int k = 0; k < chunks_2_2[i][j]->buildings.size(); k++) {
                chunks_2_2[i][j]->buildings[k]->Tick(delta);
            }
        }
    }
    for (int i = 0; i < chunks_2_3.size(); i++) {
        for (int j = 0; j < chunks_2_3[i].size(); j++) {
            if (chunks_2_3[i][j] != nullptr)
            for (int k = 0; k < chunks_2_3[i][j]->buildings.size(); k++) {
                chunks_2_3[i][j]->buildings[k]->Tick(delta);
            }
        }
    }
    for (int i = 0; i < chunks_2_4.size(); i++) {
        for (int j = 0; j < chunks_2_4[i].size(); j++) {
            if (chunks_2_4[i][j] != nullptr)
            for (int k = 0; k < chunks_2_4[i][j]->buildings.size(); k++) {
                chunks_2_4[i][j]->buildings[k]->Tick(delta);
            }
        }
    }

    for (int i = 0; i < chunks_1_1.size(); i++) {
        if (chunks_1_1[i] != nullptr)
        for (int j = 0; j < chunks_1_1[i]->buildings.size(); j++) {
            chunks_1_1[i]->buildings[j]->Tick(delta);
        }
    }
    for (int i = 0; i < chunks_1_2.size(); i++) {
        if (chunks_1_2[i] != nullptr)
        for (int j = 0; j < chunks_1_2[i]->buildings.size(); j++) {
            chunks_1_2[i]->buildings[j]->Tick(delta);
        }
    }
    for (int i = 0; i < chunks_1_3.size(); i++) {
        if (chunks_1_3[i] != nullptr)
        for (int j = 0; j < chunks_1_3[i]->buildings.size(); j++) {
            chunks_1_3[i]->buildings[j]->Tick(delta);
        }
    }
    for (int i = 0; i < chunks_1_4.size(); i++) {
        if (chunks_1_4[i] != nullptr)
        for (int j = 0; j < chunks_1_4[i]->buildings.size(); j++) {
            chunks_1_4[i]->buildings[j]->Tick(delta);
        }
    }

    for (int i = 0; i < chunks_0_1->buildings.size(); i++) {
        chunks_0_1->buildings[i]->Tick(delta);
    }

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        if (currentLevel->hand[1] != 0 && currentLevel->hand[0] < items.totalbuildings) {
            if (!gui.GuiObstructsPoint(GetMousePosition())) {
                BuildingManager::BuildBuilding(currentLevel->hand[0]);
                currentLevel->hand[1] -= 1;
            }
        } else {
            ChunkObject pp = currentLevel->chunks->GetPixelPosChunkObject(GetMousePosition());

            Chunk* chunk = currentLevel->chunks->GetChunk({ pp.cX, pp.cY });
            for (int i = 0; i < chunk->buildings.size(); i++) {
                if (chunk->buildings[i]->pos.X == pp.tX) {
                    if (chunk->buildings[i]->pos.Y == pp.tY) {
                        chunk->buildings[i]->OnOpen();
                    }
                }
            }
        }
    }
}

ChunkObject ChunkManager::GetPixelPosChunkObject(Vector2 screenPos) {
    float chunkPixelSize = TexturePixels * ChunkSize;

    // 1. world position
    float worldX = (screenPos.x - drawer.screensize.x / 2) / currentLevel->zoom - currentLevel->playerPos.x;
    float worldY = (screenPos.y - drawer.screensize.y / 2) / currentLevel->zoom - currentLevel->playerPos.y;

    // 2. chunk indices
    int chunkX = floor(worldX / chunkPixelSize);
    int chunkY = floor(worldY / chunkPixelSize);

    // 3. tile indices w chunce
    float localX = worldX - chunkX * chunkPixelSize;
    float localY = worldY - chunkY * chunkPixelSize;

    int tileX = floor(localX / TexturePixels);
    int tileY = floor(localY / TexturePixels);

    return { chunkX, chunkY, tileX, tileY };
};