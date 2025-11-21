#pragma once

#include "../define.h"


#include "../raygui.h"

enum ScreenSector : uint {
	Center,
	Top_left,
	Top_right,
	Buttom_left,
	Buttom_right
};

class Gui {
public:
	Gui();
	void init();

	void draw();

	uint GuiGetGUID();

	void GuiFreeSector(ScreenSector sector);

	void GuiOverrideSector(ScreenSector sector, uint GUID);

	bool GuiObstructsPoint(Vector2 pos);	

	uint GuiGetGUIDSector(ScreenSector sector);

	void GuiFreeGUID(uint GUID);

private:

	uint nextGUID = 2;

	uint center = 0;
	uint top_left = 0;
	uint top_right = 0;
	uint buttom_left = 0;
	uint buttom_right = 0;

	bool drawDebugInfo = false;

};