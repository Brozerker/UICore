#pragma once

#include "Player.h"


#define GAMECLASS Game::Instance()
//you can use GAMECLASS->getPlayer() to get the player from the game instance

class Game
{
public:
	static Game* Instance();
	Player getPlayer() { return gamePlayer; }
private:
	Game(Game const&) {};
	Game& operator=(Game const&) {}
	static Game* Singleton;
	Player gamePlayer;
}
