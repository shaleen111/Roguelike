#include "Map.h"
#include "TunnelAlgorithm.h"
#include "Engine.h"




Map::Map(int width, int height) : width(width), height(height)
{
	tiles = new Tile[width*height];
	generator = new TunnelAlgorithm(ROOM_MAX_SIZE, ROOM_MIN_SIZE, ROOM_MAX_NUM, width, height);
	map = new TCODMap(width, height);
	generator->GenerateLevel(map);
	camera = new Camera();

}


Map::~Map() {
	delete map;
	delete[] tiles;
	delete generator;
	delete camera;
}


bool Map::isWall(int x, int y) const{
	return !map->isWalkable(x,y);
}
void Map::render() const {
	static const TCODColor darkWall(0, 0, 100);
	static const TCODColor darkGround(50, 50, 150);
	static const TCODColor lightWall(130, 110, 50);
	static const TCODColor lightGround(200, 180, 50);
	static const TCODColor unexploredW(98, 97, 97);
	static const TCODColor unexploredG(71, 71, 71);
	static const TCODColor hackerGreen(32, 194, 14);


	for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++) {
			int camX = x + camera->cX;
			int camY = y + camera->cY;
			if (isInFOV(camX, camY)) {
				TCODConsole::root->setCharBackground(camX, camY, isWall(x, y) ? lightWall : lightGround);
			}
			else {
				TCODConsole::root->setCharBackground( camX, camY, isWall(x, y) ? darkWall : darkGround);
			}

		}
	}
}

bool Map::isInFOV(int x, int y) const {
	if (map->isInFov(x,y)){
		tiles[x + y*width].explored = true;
		return true;
	}
	return false;
}


bool Map::isExplored(int x, int y) const {
	return tiles[x + y*width].explored;
}


void Map::computeFOV() {
	map->computeFov(engine.player->x, engine.player->y, engine.fovRadius);
}