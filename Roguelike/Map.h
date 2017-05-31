#ifndef MAP_H
#define MAP_H

#include <vector>
#include <algorithm>
#include "libtcod/libtcod.hpp"
#include "TunnelAlgorithm.h"


class TunnelAlgorithm;

struct Tile {
	bool canWalk;
	Tile() : canWalk(false) {}
};

class Map
{
public:
	const int ROOM_MAX_SIZE = 8;
	const int ROOM_MIN_SIZE = 4;
	const int ROOM_MAX_NUM = 2;
	int width, height;
	Map(int width, int height);
	~Map();
	bool isWall(int x, int y) const;
	void render() const;
protected:
	std::vector<Tile> tiles;
	TunnelAlgorithm* generator;
	void setWall(int x, int y);
};
#endif

