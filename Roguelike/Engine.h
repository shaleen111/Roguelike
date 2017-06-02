#ifndef ENGINE_H
#define ENGINE_H
#include "Map.h"
#include "Actor.h"



class Engine
{
public:
	TCODList<Actor* > actors;
	Actor *player;
	Map *map;
	int fovRadius;

	Engine();
	~Engine();
	void update();
	void render();
	void setCompute(bool val);
private:
	bool computeFOV;
};

extern Engine engine; 
#endif
