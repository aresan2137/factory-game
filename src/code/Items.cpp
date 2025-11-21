#include "items.h"

#include "../define.h"

#include "Level.h"
#include "Drawer.h"
#include "Managers/TextureManager.h"
#include "Managers/BinaryManager.h"


Items::Items() {}
void Items::init() {}

void Items::DrawInventory(std::vector<unsigned short>& items, Vector2 offset, int slots) {
	std::vector<int> type;
	type.resize(slots);
	std::vector<int> count;
	count.resize(slots);
	int rep = -1;

	int item = 0;
	while (item < AllItems) {
		if (items[item] == 0) {
			item++;
			continue;
		}
		int con = items[item] / stacks[item];
		int coni = items[item] % stacks[item];
		if (coni != 0) {
			while (true) {
				rep++;
				type[rep] = item;
				con--;
				if (con <= -1) break;
				count[rep] = stacks[item];
			}
			count[rep] = items[item] % stacks[item];
			item++;
		} else {
			while (con > 0) {
				rep++;
				type[rep] = item;
				count[rep] = stacks[item];
				con--;
			}
			item++;
		}
	}

	for (item = 0; item < type.size(); item++) {
		Vector2 pos = Vector2Add(offset, { 50.0f * (item % 8),50.0f * (item / 8) });
		if (DrawItem(type[item], count[item], pos, true)) {
			items[currentLevel->hand[0]] += currentLevel->hand[1];
			items[type[item]] -= count[item];
			currentLevel->hand[0] = type[item];
			currentLevel->hand[1] = count[item];
		}
	}
}

bool Items::DrawItem(int id, int count, Vector2 pos, bool back) {
	Rectangle rec = { pos.x,pos.y,40,40 };

	if (back) DrawRectangleRec(rec, TRANSGRAY);

	if (count != 0) {
		DrawTextureEx(textures.GetTextureFromItemsAtlas(id), pos, 0, 5, WHITE);

		std::string textS = std::to_string(count);
		const char* text = textS.c_str();
		float start = (pos.x + 40.0f - 5.0f) - MeasureText(text, 25);

		DrawText(text, start, pos.y + 20, 25, BLACK);
		DrawText(text, start, pos.y + 21, 25, BLACK);

		DrawText(text, start + 1, pos.y + 20, 25, BLACK);
		DrawText(text, start + 1, pos.y + 21, 25, BLACK);
	}

	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
		if (CheckCollisionPointRec(GetMousePosition(), rec)) {
			return true;
		}
	}

	return false;
}
