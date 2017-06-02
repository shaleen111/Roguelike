#include "libtcod/libtcod.hpp"
#include "Map.h"
#include "Engine.h"


Engine::Engine(): fovRadius(10), computeFOV(true) {
	TCODConsole::setCustomFont("tileset.png", TCOD_FONT_LAYOUT_ASCII_INROW);
	TCODConsole::initRoot(80, 50, "Syrsa", true);
	player = new Actor(40, 25, '@', TCODColor::white);
	actors.push(player);
	map = new Map(100, 70);
}


Engine::~Engine()
{
	actors.clearAndDelete();
	delete map;
}

void Engine::update() {
	TCOD_key_t key;
	TCODSystem::checkForEvent(TCOD_EVENT_KEY_PRESS, &key, NULL);
	switch (key.vk) {
	case TCODK_UP:
		if (!map->isWall(player->x, player->y - 1)) {
			player->y--;
			computeFOV = true;
		}
		break;
	case TCODK_DOWN:
		if (!map->isWall(player->x, player->y + 1)) {
			player->y++;
			computeFOV = true;
		}
		break;
	case TCODK_LEFT:
		if (!map->isWall(player->x - 1, player->y)) {
			player->x--;
			computeFOV = true;
		}
		break;
	case TCODK_RIGHT:
		if (!map->isWall(player->x + 1, player->y)) {
			player->x++;
			computeFOV = true;
		}
		break;
	default:break;
	}
	if (computeFOV) {
		map->computeFOV();
	}
}

void Engine::render() {
	TCODConsole::root->clear();
	map->render();

	for (Actor **i = actors.begin(); i != actors.end(); i++ ) {
		Actor* actor = *i;
		if (map->isInFOV(actor->x, actor->y)) {
			(*i)->render();
		}
	}
}

void Engine::setCompute(bool val) {
	computeFOV = val;
}