#include "Map.h"
#include "TunnelAlgorithm.h"
#include "libtcod/libtcod.hpp"
#include <algorithm>

Rect::Rect(int x1, int y1, int w, int h) : x1(x1), y1(y1), x2(x1 + w), y2(y1 + h), centerX((x1+(x1 + w))/2), centerY((y1+(y1 + h))/2){

}


Rect::Rect() : x1(40), y1(25), x2(80), y2(65), centerX(60), centerY(45) {

}


bool Rect::intersects(Rect &r2) {
	return ((x1 <= r2.x2 && x2 >= r2.x1) && (y1 <= r2.y2 && r2.y2 >= r2.y1));
}


TunnelAlgorithm::TunnelAlgorithm(int rMax, int rMin, int rMaxRoom, int mWidth, int mHeight): ROOM_MAX_SIZE(rMax), ROOM_MIN_SIZE(rMin), ROOM_MAX_NUM(rMaxRoom), mWidth(mWidth), mHeight(mHeight)
{
	mtiles = new Tile[mWidth * mHeight];
}


TunnelAlgorithm::~TunnelAlgorithm()
{
	delete[] mtiles;
}

Tile* TunnelAlgorithm::GenerateLevel() {
	Rect* rooms;
	rooms = new Rect[ROOM_MAX_NUM];
	int numRooms = 0;
	for (int i = 0; i < ROOM_MAX_NUM; i++) {
		TCODRandom* rng = TCODRandom::getInstance();
		int w = rng->getInt(ROOM_MIN_SIZE, ROOM_MAX_SIZE);
		int h = rng->getInt(ROOM_MIN_SIZE, ROOM_MAX_SIZE);
		int x = rng->getInt(0, (mWidth -1)  - w );
		int y = rng->getInt(0, (mHeight - 1 )- h - 1);

		Rect* nRoom = new Rect(x,y,w, h);

		bool rGFail = false;

		for (int j = 0; j < numRooms; j++){
			if (nRoom->intersects(rooms[j])) {
				rGFail = true;
				break;
			}
		}
		 
		if (!rGFail) {
			createRoom(*nRoom);
			int newX = nRoom->centerX;
			int newY = nRoom->centerY;

			if (numRooms != 0) {
				int prevX = rooms[numRooms - 1].centerX;
				int prevY = rooms[numRooms - 1].centerY;

				if (rng->getInt(0, 1) == 1) {
					createHTunnel(prevX, newX, prevY);
					createVTunnel(prevY, newY, newX);
				}
				else {
					createVTunnel(prevY, newY, prevX);
					createHTunnel(prevX, newX, newY);
				}
			}
			rooms[numRooms] = *nRoom;
			delete nRoom;
			numRooms += 1;
		}
	}
	delete[] rooms;
	return mtiles;
}

void TunnelAlgorithm::createRoom(Rect& room){
	for (int x = room.x1; x <= room.x2; x++) {
		for (int y = room.y1; y <= room.y2; y++) {
			mtiles[x + (y*mWidth)].canWalk = true;
		}
	}
}


void TunnelAlgorithm::createHTunnel(int x1, int x2, int y){
	int m = std::max(x1, x2);
	for (int x= std::min(x1, x2); x <= m; x++) {
		mtiles[x + y*mWidth].canWalk = true;
	}
}


void TunnelAlgorithm::createVTunnel(int y1, int y2, int x){
	int m = std::max(y1, y2);
	for (int y = std::min(y1, y2); y <= m; y++) {
		mtiles[x + y*mWidth].canWalk = true;
	}
}