#include "libtcod/libtcod.hpp"
#include "Map.h"
#include "Engine.h"

Engine engine;

int main() {
	while (!TCODConsole::isWindowClosed()) {
		engine.update();
		engine.render();
		TCODConsole::flush();
	}
	return 0;
}	