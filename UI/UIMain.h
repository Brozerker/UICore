//Who needs what?
//Main:
//	update functions
//	gamestate change
//Graphics:
//	position & filename of sprites
//Physics:
//	Size & position of buttons
#pragma once
#include "..\EngineDemo\GameState.h"
#include "..\D3D9Graphics\GFX.h"
#include "defines.h"
#include <vector>
#include "..\Main\DirectInput.h"
#include "..\Main\Player.h"
#include "..\EngineDemo\Game.h"
using namespace std;
using GFXCore::SpriteData;


class UIMain {
protected:
	Player * player;
	GAMESTATE currentState;
	//GFXCore::Graphics gfx;
	// Stores the position of sprites that LoadSprite loads into an array so that they can be accessed later
	vector<int> menuSpriteIDs;
	vector<int> gameSpriteIDs;
	vector<int> pauseSpriteIDs;
	vector<int> exitSpriteIDs;
	int currentScore;
	int missileAmmo;
	RECT hpBarSize;

private:
	bool spriteClicked(DirectInput &suppliedInput, int spriteID)
	{
		if (suppliedInput.MouseDX() >  GFX->getSpritePosX(spriteID) && suppliedInput.MouseDX() < GFX->getSpritePosX(spriteID) + GFX->getSpriteWidth(spriteID)) 
		{
			if (suppliedInput.MouseDY() > GFX->getSpritePosY(spriteID) && suppliedInput.MouseDY() < GFX->getSpritePosY(spriteID) + GFX->getSpriteHeight(spriteID))
			{
				return true;
			}
		}
		return false;
	}
	
public:

	UIMain(): currentState(STATE_INIT), currentScore(0), missileAmmo(0) {
//		player = &(PLAYER);//Instance()->player);
		hpBarSize.top = 350;
		hpBarSize.bottom = 400;
		hpBarSize.left = 100;
		hpBarSize.right = 500;
	}
	~UIMain() {}

	
	void updateMenu() {
		// tells graphics what to draw
		GFX->addToSpriteRenderList(&menuSpriteIDs[0], menuSpriteIDs.size());

		// check for mouse input
		int MOUSE_LEFT = 0;
		if (INPUT->MouseButtonDown(MOUSE_LEFT))
		{
			if (spriteClicked(*INPUT, menuSpriteIDs[START]))
			{
				currentState = STATE_PLAY;
			}

			if (spriteClicked(*INPUT, menuSpriteIDs[CREDITS]))
			{
				currentState = STATE_CREDIT;
			}
		}
		GFX->setTextForFont(GFX->loadFont((GFXCore::FontData&)"..\\EngineDemo\\Content\\Font\\Delicious-Roman.otf"), (wchar_t*)"hello");
	}



	void updateGame() {
		//GFX->loadFont((GFXCore::FontData&)"..\\EngineDemo\\Content\\Font\\Delicious-Roman.otf");
//		int healthSize = PLAYER.getMaxHealth();
//		int currAmmo = PLAYER.getMissileAmmo();
		// tells graphics what to draw
		GFX->addToSpriteRenderList(&gameSpriteIDs[0], gameSpriteIDs.size());
		// update health bar and number of missiles
		
		//Health bar update
//		for(healthSize; healthSize > PLAYER.getHealth(); --healthSize) //reduce the health bar size from the difference.
		{
//			hpBarSize.right = 500 * (healthSize / 100);
			GFX->updateSprite(gameSpriteIDs.at(HEALTH), D3DXVECTOR3(370, 710, 0.0f), hpBarSize); // update the information
			
			
		}
		
		GFX->setTextForFont(GFX->loadFont((GFXCore::FontData&)"..\\EngineDemo\\Content\\Font\\Delicious-Roman.otf"), (wchar_t*)"Ammo : %i");
		GFX->setTextForFont(GFX->loadFont((GFXCore::FontData&)"..\\EngineDemo\\Content\\Font\\Delicious-Roman.otf"), (wchar_t*)"Score : %i");
		//Missle Bar Update
		//for (int i = 0; i < )
		//GFX->text->updateText(currAmmogetMissile//update the information
		
		// Main has getHealth(), getMaxHealth(), and getMissileAmmo() functions that we can use. 
		//  They've also provided me with their code. I haven't uploaded it, but if you want to 
		//  see it, let me know.
	}

	void updatePause(const bool paused) {
		if (paused)
		{
			GFX->addToSpriteRenderList(&pauseSpriteIDs[0], pauseSpriteIDs.size());
			if (spriteClicked(*INPUT, pauseSpriteIDs[BACK]))
			{
				//paused = false;
			}
		}
	}
	void updateExit() {
		// tell Graphics which sprites to draw
		GFX->addToSpriteRenderList(&exitSpriteIDs[0], exitSpriteIDs.size());
		currentState = STATE_EXIT;
	}
};