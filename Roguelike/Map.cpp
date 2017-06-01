#include "Map.h"
#include "TunnelAlgorithm.h"

Map::Map(int width, int height) : width(width), height(height)
{
	tiles = new Tile[width*height];
	generator = new TunnelAlgorithm(ROOM_MAX_SIZE, ROOM_MIN_SIZE, ROOM_MAX_NUM, width, height);
	tiles = generator->GenerateLevel();
}



bool Map::isWall(int x, int y) const{
	return !tiles[x + y*width].canWalk;
}
void Map::render() const {
	static const TCODColor darkWall(0, 0, 100);
	static const TCODColor darkGround(50, 50, 150);

	for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++){
			TCODConsole::root->setCharBackground(x, y, isWall(x,y) ? darkWall : darkGround);
		}
	}
}
