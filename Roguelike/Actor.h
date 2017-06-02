#ifndef ACTOR_H
#define ACTOR_h

class Actor
{
public:
	int x, y;
	int ch;
	TCODColor col;
	 
	Actor(int x, int y, int ch, const TCODColor& col);
	void render(int nX, int nY) const;
};
#endif
