//Game class created by Darrell Smith and edited by Brent Spector

#include "Game.h"

#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

#include "../D3D9Graphics/GFX.h"
#include "DirectInput.h"
#include "Logger.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, PSTR, int)
{
	Game::Instance();
	srand((unsigned)time(NULL));
	if (!GFX->initGFX(hInstance, L"Space Game"))
		LOGGER->Write(L"WinMain: Could not initialized graphics core", true);
	Game::Instance()->Run();
	Game::Instance()->Delete();
	return 1;
}

void Game::Run()
{
	
	//initialize timing
	__int64 cntsPerSec = 0;
	QueryPerformanceFrequency((LARGE_INTEGER*)& cntsPerSec);
	float secsPerCnt = 1.f / (float)cntsPerSec;
	__int64 prevTimeStamp = 0;
	QueryPerformanceCounter((LARGE_INTEGER*)& prevTimeStamp);
	//loop until it's time to quit
	init();
	while (!QuitNow)
	{
		//keep windows busy
		MSG msg;
		if(PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);

			if(msg.message == WM_CLOSE || msg.message == WM_QUIT)
				QuitNow = true;
		}
		//check if device is lost, run code if it isn't, otherwise IsDeviceLost() will
		//reset things
		if (!IsDeviceLost())
		{
			__int64 currTimeStamp = 0;
			QueryPerformanceCounter((LARGE_INTEGER*)&currTimeStamp);
			float dt = (currTimeStamp - prevTimeStamp)*secsPerCnt;
			update(dt);
			render();
			//current time stamp becomes the previous time stamp for the next iteration.
			prevTimeStamp = currTimeStamp;
		}
	}
	shutdown();
}

//global initialization to facilitate singleton design pattern
Game* Game::Singleton = NULL;

//retrieve singleton instance
Game* Game::Instance()
{
	if (Singleton == 0)
		Singleton = new Game;
	return Singleton;
}

void Game::Delete()
{
	if (Singleton)
	{
		delete Singleton;
		Singleton = NULL;
	}
}

void Game::init()
{
	App::init();
	States[STATE_INIT] = new InitState();
	States[STATE_MENU] = new MenuState();
	States[STATE_CREDIT] = new CreditsState();
	States[STATE_PLAY] = new PlayState();
	States[STATE_EXIT] = new ExitState();
	//will always start with the Init and then Menu states
	States[STATE_INIT]->init();
	States[STATE_MENU]->init();
// 	States[STATE_CREDIT]->init();
// 	States[STATE_PLAY]->init();
// 	States[STATE_EXIT]->init();
	// TODO: change later to be STATE_MENU
	State = STATE_PLAY;
	QuitNow = false;
	GFX->initModules();

//	gamePhysics = physics();
	
	nPlayerModel = GFX->loadModel(L"Content\\Models\\PlayerSpaceshipV2.x");
	player.init(nPlayerModel, -1);
	player.setPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	player.setFixedRotation(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//player.toggleEnabled();

	PROJECTILES.initBulletProjectiles(GFX->createSphereMesh(5.0f, 25, 25), -1);
	PROJECTILES.initMissileProjectiles(GFX->createCylinderMesh(5.0f, 15.0f, 5.0f, 25, 25), -1);

	GFX->cameraSetLens(GFX->windowWidth(), GFX->windowHeight(), -1000.0f, 1000.0f);

	gamePhysics.GameObjectManager->addBoxDynamicRigidBody("player", 0, 0, 25, 25, true, &PLAYER.physObj);
	PLAYER.physObj.setCollissionCategory((uint16) gameObjectCollissionCategory::gocPLAYER); // I am a player
	PLAYER.physObj.setCollissionMask((uint16) gocPLAYER || gocMISSLE || gocPICKUP ||gocBOUNDARY || gocENEMY); // i can collide with 
	gamePhysics.startWorld();
	
	gameUI.init();
}

void Game::onLostDevice()
{
	States[State]->onLostDevice();
}

void Game::onResetDevice()
{
	States[State]->onLostDevice();
}

void Game::update(const float dt)
{
	static float counter = 0.0f;
	counter += dt;
	if (counter >= 0.033333333334f)
	{
		gamePhysics.updateWorld(dt);
		counter = 0.0f;
	}
	
	States[State]->update(dt);
	GFX->addToModelRenderList(&player);
	//GFX->updateModel(nPlayerModel, player.getPosition());
	gameUI.update(dt, State, paused);
}

void Game::render()
{
	States[State]->render();
//	GFX->updateModel(nPlayerModel, player.getPosition());
//	GFX->renderScene();
}

void Game::shutdown()
{
	//will always end by exiting through the menu state
	States[STATE_MENU]->shutdown();
	States[STATE_EXIT]->shutdown();

	for (int i = 0; i < NUM_STATES; ++i) {
		delete States[i];
		States[i] = NULL;
	}

}

void Game::changeState(GAMESTATE newstate)
{
	if(newstate != State)
	{
		States[State]->shutdown();
		State = newstate;
		States[State]->init();
		paused = false;
	}
}
