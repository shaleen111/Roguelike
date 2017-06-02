#include "libtcod/libtcod.hpp"
#include "Actor.h"

Actor::Actor(int x, int y, int ch, const TCODColor &col) : x(x), y(y), ch(ch), col(col)
{}


void Actor::render(int nX, int nY) const{
	TCODConsole::root->putChar(nX,nY,ch);
	TCODConsole::root->setCharForeground(nX, nY, col);
}