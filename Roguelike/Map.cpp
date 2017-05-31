#include "Map.h"


Map::Map(int width, int height) : width(width), height(height)
{
	tiles.resize(width*height);
	std::fill(tiles.begin(), tiles.begin() + (width*height), new Tile());
	generator = new TunnelAlgorithm(ROOM_MAX_SIZE, ROOM_MIN_SIZE, ROOM_MAX_NUM, width, height);

}


Map::~Map()
{
}

bool Map::isWall(int x, int y) const{
	return !tiles[x + y*width].canWalk;
}
void Map::render() const {
	static const TCODColor darkWall(0, 0, 100);
	static const TCODColor darkGround(50, 50, 150);

	for (int x = 0; x < width; ++x) {
		for (int y = 0; y < height; ++y) {
			TCODConsole::root->setCharBackground(x, y, isWall(x,y) ? darkWall : darkGround);
		}
	}
}

void Map::setWall(int x, int y) {
	tiles[x + y*width].canWalk = false;
}