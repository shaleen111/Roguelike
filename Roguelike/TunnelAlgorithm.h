#ifndef TUNNELALGORITHM_H
#define TUNNELALGORITHM_H

struct Rect {
	int x1; 
	int y1;
	int x2;
	int y2;
	int centerX;
	int centerY;

	Rect(int x1, int y1, int w, int h);
	bool intersects(Rect *r2);
};
class TunnelAlgorithm
{
public:
	int mWidth;
	int mHeight;
	TunnelAlgorithm(int rMax, int rMin, int rMaxRoom, int mWidth, int mHeight);
	~TunnelAlgorithm();
	Tile* GenerateLevel();
private:
	Tile* mtiles;
	const int ROOM_MAX_SIZE;
	const int ROOM_MIN_SIZE;
	const int ROOM_MAX_NUM;
	void createRoom(Rect* room);
	void createHTunnel(int x1, int x2, int y);
	void createVTunnel(int y1, int y2, int x);
};

#endif