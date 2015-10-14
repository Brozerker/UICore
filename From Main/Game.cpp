#include "Game.h"


Game* Game::Singleton = NULL;

Game* Game::Instance()
{
	if (Singleton == 0)
		Singleton = new Game;
	return Singleton;
}
