#include "Map.h"
#include "TunnelAlgorithm.h"
#include "Engine.h"


void Camera::moveCam(int ax, int ay) {
	//cam is in limits here
	if (ax < 0) ax = 0;
	if (ay < 0) ay = 0;
	// - 1 account for player
	if (ax > engine.map->width - 1) ax = engine.map->width - 1;
	if (ay > engine.map->height - 1) ay = engine.map->height - 1;

	cX = ax;
	cY = ay;
}


int Camera::convertX(int ax) {
	if (ax > w) return 0;
	return ax;
}


int Camera::convertY(int ay) {
	if (ay > h) return 0;
	return ay;
}


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

	camera->moveCam(engine.player->x, engine.player->y);

	for (int x = 0; x < camera->w; x++) {
		for (int y = 0; y < camera->h; y++) {
			int mX = camera->cX + x;
			int mY = camera->cY + y;
			if (isInFOV(mX, mY)) {
				TCODConsole::root->setCharBackground(x, y, isWall(mX, mY) ? lightWall : lightGround);
			}
			else {
				TCODConsole::root->setCharBackground( x, y, isWall(mX, mY) ? darkWall : darkGround);
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