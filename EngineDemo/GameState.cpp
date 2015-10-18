//GameState classes created by Darrell Smith and edited by Brent Spector
#include "GameState.h"

//some things seem to be occurring the same in every state, so some of this may be moved
//back to the main methods in Game

#include "../D3D9Graphics/GFX.h"
#include "../Main/DirectInput.h"
#include "../Main/Logger.h"
#include "Game.h"

void InitState::init()
{
	LOGGER->open();
	INPUT->init(DISCL_NONEXCLUSIVE | DISCL_FOREGROUND, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);

//	GAMECLASS->gameAudio.init();
//	GAMECLASS->gameUI.init();
}

void InitState::shutdown()
{
	//need to define because ChangeState automatically calls it, but don't actually need to do anything here
}

void MenuState::init()
{
	//?
}

void MenuState::update(const float dt)
{
	//	GAMECLASS->gameAudio.update(dt);
	INPUT->Poll();
	// PHYSICS: add update
	//GAMECLASS->gameUI.update(dt, STATE_MENU);
	//GAMECLASS->changeState(GAMECLASS->gameUI.checkStateChanges());
}

void MenuState::render()
{
	GFX->renderScene();
}

void MenuState::onLostDevice()
{
	GFX->onLostDevice();
	//GAMECLASS->gameAudio.onLostDevice();
}

void MenuState::onResetDevice()
{
	GFX->onResetDevice();
	//GAMECLASS->gameAudio.onResetDevice();
}

void MenuState::shutdown()
{
	//?
}

void CreditsState::init()
{
	//?
}

void CreditsState::update(const float dt)
{
	INPUT->Poll();
	// PHYSICS: add update
	//GAMECLASS->gameAudio.update(dt);
	//GAMECLASS->gameUI.update(dt, STATE_CREDIT);
	//GAMECLASS->changeState(GAMECLASS->gameUI.checkStateChanges());
}

void CreditsState::render()
{
	GFX->renderScene();
}

void CreditsState::onLostDevice()
{
	GFX->onLostDevice();
	//GAMECLASS->gameAudio.onLostDevice();
}

void CreditsState::onResetDevice()
{
	GFX->onResetDevice();
	//GAMECLASS->gameAudio.onResetDevice();
}

void CreditsState::shutdown()
{
	//?
}

void PlayState::init()
{
	//GAMECLASS->gameAI.init();
	//GAMECLASS->gamePhysics.init();
	GAMECLASS->player = Player();
	PLAYER.init(GAMECLASS->nPlayerModel, -1);
	//load model/texture resources
	//init player
	//PLAYER.init(1,1);//need to get what IDs to use from graphics
	//init graphics textures for ui and pause menu
}

void PlayState::update(const float dt)
{
	INPUT->Poll();
	GAMECLASS->gamePhysics.updateWorld();

	static float pausecooldown = 0.f;
	if(pausecooldown > 0.f)
		pausecooldown -= dt;
	//GAMECLASS->gameAudio.update(dt);
	//listen for input
	if (INPUT->KeyDown(DIK_ESCAPE) && pausecooldown <= 0.f)
	{
		GAMECLASS->togglePause();
		pausecooldown = .5f;
	}
	if(GAMECLASS->paused)
	{
		//GAMECLASS->gameUI.update(dt, STATE_PLAY, true);
	}
	else
	{
		//only do any of this if the player is alive
		if(PLAYER.isEnabled())
		{
			//listen for player input
			//the cool down for bullet and missile firing is built into the player class
			if(INPUT->KeyDown(DIK_SPACE))
				PLAYER.fireBullet();
			if(INPUT->KeyDown(DIK_F))
				PLAYER.fireMissile();
			//player movement
			float x, y;
			if(INPUT->KeyDown(DIK_W))
				y = 1.f;
			else if(INPUT->KeyDown(DIK_S))
				y = -1.f;
			else
				y = 0.f;
			if(INPUT->KeyDown(DIK_A))
				x = -1.f;
			else if(INPUT->KeyDown(DIK_D))
				x = 1.f;
			else
				x = 0.f;
			PLAYER.getPhys().applyForceFromCenter(x, y);
			D3DXVECTOR3 pos;
			pos.x = PLAYER.getPhys().x  * dt * 100;
			pos.y = PLAYER.getPhys().y  * dt * 100;
			pos.z = 0.0f;
			PLAYER.setPosition(pos/*PLAYER.getPosition() + PLAYER.getVelocity() * dt * 100*/);
			//update AI/physics first so they can flag objects
			//GAMECLASS->gameAI.update(dt);
			//GAMECLASS->gamePhysics.update(dt);
			//then we update the objects to see which are flagged
			PLAYER.update(dt);
			ASTEROIDS.update(dt);
			ENEMIES.update(dt);
			PICKUPS.update(dt);
			PROJECTILES.update(dt);
			//GAMECLASS->gameUI.update(dt, STATE_PLAY);
		}
	}
	//after updating, check for any state changes due to UI things
	//GAMECLASS->changeState(GAMECLASS->gameUI.checkStateChanges());
}

void PlayState::render()
{
	GFX->renderScene();
}

void PlayState::onLostDevice()
{
	GFX->onLostDevice();
	//GAMECLASS->gameAudio.onLostDevice();
}

void PlayState::onResetDevice()
{
	GFX->onResetDevice();
	//GAMECLASS->gameAudio.onResetDevice();
}

void PlayState::shutdown()
{
	//clear out previous play stuff from managers
	PLAYER.shutdown();
	ASTEROIDS.clear();
	ENEMIES.clear();
	PICKUPS.clear();
	PROJECTILES.clear();
	//unload models/textures for game play, UI, pause menu
	//GAMECLASS->gameAI.shutdown();
	//GAMECLASS->gamePhysics.shutdown();
}


void ExitState::init()
{
	
	
	LOGGER->close();
	//unload main graphics/UI/audio resources and then quit
	//GAMECLASS->gameUI.shutdown();
	//GAMECLASS->gameAudio.shutdown();
	GFX->shutdown();
	INPUT->shutdown(); 
	GAMECLASS->gamePhysics.endWorld();
}


