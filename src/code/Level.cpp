#include "Level.h"

#include "managers/ChunkManager.h"

Level::Level() {
    chunks = new ChunkManager();
}

Level::~Level() {
    delete chunks;
}