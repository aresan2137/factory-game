#include "BuildingManager.h"

#include "../../../define.h"

#include "../../Level.h"
#include "../ChunkManager.h"
#include "../../Chunk.h"
#include "Building.h"

namespace BuildingManager {
	void BuildBuilding(int type) {
		ChunkObject pp = currentLevel->chunks->GetPixelPosChunkObject(GetMousePosition());
		
		Building* build = new Building(type);
		build->pos.X = pp.tX;
		build->pos.Y = pp.tY;

		currentLevel->chunks->GetChunk({ pp.cX,pp.cY })->buildings.push_back(build);
	}
}
