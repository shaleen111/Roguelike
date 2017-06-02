#include "Map.h"
#include "TunnelAlgorithm.h"
#include "Engine.h"

int Camera::getCX(int x) {
	int cx = x - cX;

	if (cx<0 || cx >= w) {
		return NULL;
	}
	return cx;
}


int Camera::getCY(int y) {
	int cy = y - cY;

	if (cy<0 || cy >= h) {
		return NULL;
	}
	return cy;
}

void Camera::move(int x, int y) {
	int cx = x - w / 2;
	int cy = y - h / 2;

	if (cx < 0) {
		cx = 0;
	}

	if (cy < 0) {
		cy = 0;
	}

	if (cx >= mW - w - 1) {
		cx = mW - w - 1;
	}

	if (cy >= mH - h - 1) {
		cy = mH - h - 1;
	}

	cX = cx; 
	cY = cy;
}

Map::Map(int width, int height) : width(width), height(height)
{
	camera = new Camera(width, height);
	tiles = new Tile[width*height];
	generator = new TunnelAlgorithm(ROOM_MAX_SIZE, ROOM_MIN_SIZE, ROOM_MAX_NUM, width, height);
	map = new TCODMap(width, height);
	generator->GenerateLevel(map);
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

	camera->move(engine.player->x, engine.player->y);


	for (int x = 0; x < camera->w; x++) {
		for (int y = 0; y < camera->h; y++) {
			int camX = x + camera->cX;
			int camY = y + camera->cY;
			if (isInFOV(x, y)) {
				TCODConsole::root->setCharBackground(x, y, isWall(camX, camY) ? lightWall : lightGround);
			}
			else if(isExplored(x, y)){
				TCODConsole::root->setCharBackground(x,y, isWall(camX, camY) ? darkWall : darkGround);
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
	map->computeFov(camera->getCX(engine.player->x), camera->getCY(engine.player->y), engine.fovRadius);
}