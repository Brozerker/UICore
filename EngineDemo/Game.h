//Game class created by Darrell Smith and edited by Brent Spector

#pragma once


#include <Windows.h>
#include <list>

//include parent class
#include "..\Main\App.h"


//include state information
#include "GameState.h"


#include "AsteroidManager.h"
#include "EnemyManager.h"
#include "PickupManager.h"
#include "Player.h"
#include "ProjectileManager.h"
//include other cores
#include "physics.h"
#include "AI.h"
#include "Audio_Interface.h"
#include "UI_Interface.h"

#pragma comment(lib, "Main.lib")
#pragma comment(lib, "AI.lib")
//#pragma comment(lib, "D3D9GraphicsD.lib")
#pragma comment(lib, "Physics.lib")
#pragma comment(lib, "Audio.lib")

#define GAMECLASS Game::Instance()
#define ASTEROIDS Game::Instance()->asteroids
#define ENEMIES Game::Instance()->enemies
#define PICKUPS Game::Instance()->pickups
#define PROJECTILES Game::Instance()->projectiles
#define PLAYER Game::Instance()->player

//this inherits from the base class App and adds things that are specific to this game or demo
class Game : public App
{
	friend class InitState;
	friend class MenuState;
	friend class CreditsState;
	friend class PlayState;
	friend class ExitState;
public:
	void Run();
	static Game* Instance();
	inline bool GetPaused() { return paused; }
	void Delete();
	//managers
	AsteroidManager asteroids;
	EnemyManager enemies;
	PickupManager pickups;
	ProjectileManager projectiles;
	Player player;
	inline GAMESTATE getState() { return State; }
protected:
	//the one instance of the object
	static Game* Singleton;
	//constructor can't be called by nonmember functions
	Game() : App(), paused(false), nPlayerModel(-1) {}
	inline GAMESTATE getGameState() { return State; }
	void changeState(GAMESTATE newstate);
private:
	//toggle the game being paused
	inline void togglePause() { paused = !paused; }
	//framework methods from the App class
	void init();//used upon game startup
	void onLostDevice();//used when screen changes size or other event causes device to be lost
	void onResetDevice();//used after onLostDevice to reaquire needed elements
	void update(const float);//update the scene every frame, anything that is not rendering goes here
	void render();//render all the visual elements of the game
	void shutdown();//used upon game exit

	physics gamePhysics;
	//the present state of the game
	GameState* States[NUM_STATES];
	//GameState States[NUM_STATES];
	GAMESTATE State;
	/*****
	AI gameAI;
	UI gameUI;
	Audio gameAudio;
	*****/
	//is game play paused
	bool paused;

	// content handlers
	int		nPlayerModel;
};

