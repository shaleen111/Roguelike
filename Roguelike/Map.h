#ifndef MAP_H
#define MAP_H

#include <vector>
#include "libtcod/libtcod.hpp"

class TunnelAlgorithm;

struct Camera {
	int cX;
	int cY;
	int w;
	int h;

	Camera():cX(0), cY(0), w(80), h(50){}
	void moveCam(int ax, int ay);
	int convertX(int ax);
	int convertY(int ay);
};
struct Tile {
	bool explored;
	Tile() : explored(false) {}
};

class Map
{
public:
	Camera* camera;
	int ROOM_MAX_SIZE = 8;
	int ROOM_MIN_SIZE = 2;
	int ROOM_MAX_NUM = 50;
	int width, height;
	Map(int width, int height);
	~Map();
	bool isWall(int x, int y) const;
	bool isInFOV(int x, int y) const;
	bool isExplored(int x, int y) const;
	void computeFOV();
	void render() const;
protected:
	TCODMap* map;
	Tile* tiles;
	TunnelAlgorithm* generator;
};
#endif

