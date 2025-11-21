#pragma once

#include "../define.h"

class Items {
public:
	Items();
	void init();

	void DrawInventory(std::vector<unsigned short>& items, Vector2 offset, int slots);

	bool DrawItem(int id, int count, Vector2 pos, bool back);

	uint AllItems = 2;
	uint totalbuildings = 2;

	std::vector<const char*> names;
	std::vector<const char*> descriptions;
	std::vector<uint> stacks;

private:

};

