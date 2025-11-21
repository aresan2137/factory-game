
#define RAYGUI_IMPLEMENTATION
#include "Gui.h"

#include "../define.h"

#include "Level.h"
#include "Drawer.h"
#include "Items.h"

Gui::Gui() {}
void Gui::init() {}

void Gui::draw() {
	if (IsKeyPressed(KEY_F9)) drawDebugInfo = !drawDebugInfo;
	if (drawDebugInfo) {
		DrawText("Debug Info:",20,20,30,BLACK);
		DrawFPS(20,50);
	}

	if (IsKeyPressed(KEY_E)) center = (center == 0)? 1 : 0;
	if (center == 1) {
		center = (GuiWindowBox({ drawer.screensize.x / 2 - 430, drawer.screensize.y / 2 - 300, 860, 600 }, "chest"))? 0 : 1;
		items.DrawInventory(currentLevel->item, { drawer.screensize.x / 2 - 420, drawer.screensize.y / 2 - 250, }, 50);
	}

	items.DrawItem(currentLevel->hand[0], currentLevel->hand[1], Vector2Add(GetMousePosition(), { 10,10 }), false);
}

uint Gui::GuiGetGUID() {
	nextGUID++;
	return nextGUID;
}

void Gui::GuiOverrideSector(ScreenSector sector, uint GUID) {
	if (sector == ScreenSector::Center) center = GUID;
	if (sector == ScreenSector::Top_left) top_left = GUID;
	if (sector == ScreenSector::Top_right) top_right = GUID;
	if (sector == ScreenSector::Buttom_left) buttom_left = GUID;
	if (sector == ScreenSector::Buttom_right) buttom_right = GUID;
}

void Gui::GuiFreeSector(ScreenSector sector) {
	if (sector == ScreenSector::Center) center = 0;
	if (sector == ScreenSector::Top_left) top_left = 0;
	if (sector == ScreenSector::Top_right) top_right = 0;
	if (sector == ScreenSector::Buttom_left) buttom_left = 0;
	if (sector == ScreenSector::Buttom_right) buttom_right = 0;
}

bool Gui::GuiObstructsPoint(Vector2 pos) {
	bool obs = false;

	if (center != 0) if (CheckCollisionPointRec(pos, { drawer.screensize.x / 2 - 430, drawer.screensize.y / 2 - 300, 860, 600 })) obs = true;

	return obs;
}

uint Gui::GuiGetGUIDSector(ScreenSector sector) {
	if (sector == ScreenSector::Center) return center;
	if (sector == ScreenSector::Top_left) return top_left;
	if (sector == ScreenSector::Top_right) return top_right;
	if (sector == ScreenSector::Buttom_left) return buttom_left;
	if (sector == ScreenSector::Buttom_right) return buttom_right;
}

void Gui::GuiFreeGUID(uint GUID) {}