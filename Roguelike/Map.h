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
	const int ROOM_MAX_SIZE = 2;
	const int ROOM_MIN_SIZE = 1;
	const int ROOM_MAX_NUM = 4;
	int width, height;
	Map(int width, int height);
	~Map();
	bool isWall(int x, int y) const;
	void render() const;
protected:
	std::vector<Tile> tiles;
	TunnelAlgorithm* generator;
};
#endif

