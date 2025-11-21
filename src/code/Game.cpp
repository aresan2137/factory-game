#include "Game.h"

#include "../define.h"

#include "Level.h"
#include "Managers/ChunkManager.h"


Game::Game() {	
}

void Game::Tick() {

	currentLevel->chunks->Tick();

	Vector2 move = { 0.0f,0.0f };

	if (IsKeyDown(KEY_W)) move.y += 1;
	if (IsKeyDown(KEY_S)) move.y -= 1;
	if (IsKeyDown(KEY_A)) move.x += 1;
	if (IsKeyDown(KEY_D)) move.x -= 1;

	currentLevel->playerPos = Vector2Add(Vector2Scale(Vector2Normalize(move), GetFrameTime() * currentLevel->playerSpeed), currentLevel->playerPos);

	if (IsKeyDown(KEY_KP_ADD)) currentLevel->zoom += GetFrameTime() * 10;
	if (IsKeyDown(KEY_KP_SUBTRACT)) currentLevel->zoom -= GetFrameTime() * 10;
	currentLevel->zoom += GetMouseWheelMove() * 1.5f;
	if (currentLevel->zoom < 1.35f) currentLevel->zoom = 1.35f;
	if (currentLevel->zoom > 12.0f) currentLevel->zoom = 12.0f;

	if (IsKeyPressed(KEY_F10)) {
		f10 = !f10;
		if (f10) {
			SetWindowState(FLAG_VSYNC_HINT);
		} else {
			ClearWindowState(FLAG_VSYNC_HINT);
		}
	} 
	if (IsKeyPressed(KEY_F11)) {
		f11 = !f11;
		if (f11) {
			SetWindowState(FLAG_FULLSCREEN_MODE);
		} else {
			ClearWindowState(FLAG_FULLSCREEN_MODE);
		}
	}
}