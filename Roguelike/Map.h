#ifndef MAP_H
#define MAP_H

#include "libtcod/libtcod.hpp"
#include "Engine.h"

class TunnelAlgorithm;

struct Camera {
	int cX;
	int cY;
	int w;
	int h;
	int mW;
	int mH;	

	Camera(int mW, int mH):cX(0), cY(0), w(80), h(50),mW(mW), mH(mH){}
	int getCX(int pX);
	int getCY(int pY);
	void move(int x, int y);
};

struct Tile {
	bool explored;
	Tile() : explored(false) {}
};

class Map
{
public:
	Camera* camera;
	int ROOM_MAX_SIZE = 12;
	int ROOM_MIN_SIZE = 8;
	int ROOM_MAX_NUM = 80;
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

