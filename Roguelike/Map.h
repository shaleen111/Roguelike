#ifndef MAP_H
#define MAP_H

#include <vector>
#include "libtcod/libtcod.hpp"

class TunnelAlgorithm;

struct Tile {
	bool canWalk;
	Tile() : canWalk(false) {}
};

class Map
{
public:
	int ROOM_MAX_SIZE = 10;
	int ROOM_MIN_SIZE = 4;
	int ROOM_MAX_NUM = 10;
	int width, height;
	Map(int width, int height);
	bool isWall(int x, int y) const;
	void render() const;
protected:
	Tile* tiles;
	TunnelAlgorithm* generator;
};
#endif

