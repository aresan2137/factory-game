#include "define.h"

#include "code/Drawer.h"
#include "code/Level.h"
#include "code/Game.h"
#include "code/Gui.h"
#include "code/Managers/Buildings/BuildingManager.h"
#include "code/Managers/TextureManager.h"
#include "code/Managers/BinaryManager.h"
#include "code/Items.h"

Drawer drawer;
Level* currentLevel = nullptr;
Gui gui;
TextureManager textures;
Items items;


int main() {

	InitWindow(1280, 720,"game");
	SetWindowState(FLAG_VSYNC_HINT);
	SetWindowState(FLAG_WINDOW_RESIZABLE);
	//SetExitKey(KEY_NULL);

	drawer.init();
	gui.init();
	textures.init();
	items.init();

	currentLevel = new Level();

	BeginDrawing();
		DrawText("Loading Please Wait", 40, 40, 80, WHITE);
	EndDrawing();

	BinaryManager::LoadFileAsItemsBin(items.stacks, items.names, items.descriptions, "resources/build/items.bin");
	

	Game game = Game();

	while (!WindowShouldClose()) {
		BeginDrawing(); 
			ClearBackground(BLACK);

			drawer.screensize = { (float)GetScreenWidth(), (float)GetScreenHeight() };

			drawer.DrawGame();

			game.Tick();

			gui.draw();			

		EndDrawing();
	}
}
