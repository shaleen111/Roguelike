#ifndef TUNNELALGORITHM_H
#define TUNNELALGORITHM_H

#include "libtcod/libtcod.hpp"

struct Rect {
	int x1; 
	int y1;
	int x2;
	int y2;
	int centerX;
	int centerY;

	Rect(int x1, int y1, int w, int h);
	Rect();
	bool intersects(Rect &r2);
};
class TunnelAlgorithm
{
public:
	int mWidth;
	int mHeight;
	TunnelAlgorithm(int rMax, int rMin, int rMaxRoom, int mWidth, int mHeight);
	~TunnelAlgorithm();
	void GenerateLevel(TCODMap* tmap);
private:
	TCODRandom* rng;
	Rect* rooms;
	TCODMap* mtiles;
	const int ROOM_MAX_SIZE;
	const int ROOM_MIN_SIZE;
	const int ROOM_MAX_NUM;
	void createRoom(Rect& room);
	void createHTunnel(int x1, int x2, int y);
	void createVTunnel(int y1, int y2, int x);
};

#endif