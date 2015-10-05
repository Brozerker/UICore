//Who needs what?
//Main:
//	update functions
//	gamestate change
//Graphics:
//	position & filename of sprites
//Physics:
//	Size & position of buttons

#include "From Main\GameState.h"
#include "From Sam\GFX.h"
#include "defines.h"
#include <vector>
#include "From Main\DirectInput.h"
using namespace std;
using GFXCore::SpriteData;


class UIMain {
protected:
	GAMESTATE currentState;
	//GFXCore::Graphics gfx;
	// Stores the position of sprites that LoadSprite loads into an array so that they can be accessed later
	vector<int> menuSpriteIDs;
	vector<int> gameSpriteIDs;
	vector<int> pauseSpriteIDs;
	vector<int> exitSpriteIDs;
	int currentScore;
	int missileAmmo;
	DirectInput input;

private:
	bool spriteClicked(DirectInput &suppliedInput, int spriteID)
	{
		if (suppliedInput.mouseDX() >  GFX->getSpritePosX(spriteID) && suppliedInput.mouseDX() < GFX->getSpritePosX(spriteID) + GFX->getSpriteWidth(spriteID)) 
		{
			if (suppliedInput.mouseDY() > GFX->getSpritePosY(spriteID) && suppliedInput.mouseDY() < GFX->getSpritePosY(spriteID) + GFX->getSpriteHeight(spriteID))
			{
				return true;
			}
		}
		return false;
	}
	
public:

	UIMain(): currentState(STATE_INIT), currentScore(0), missileAmmo(0) {}
	~UIMain();

	
	void updateMenu() {
		// tells graphics what to draw
		GFX->addToSpriteRenderList((int*)menuSpriteIDs[0], menuSpriteIDs.size());

		// check for mouse input
		int MOUSE_LEFT = 0;
		if (input.mouseButtonDown(MOUSE_LEFT))
		{
			if (spriteClicked(input, menuSpriteIDs[START]))
			{
				currentState = STATE_PLAY;
			}

			if (spriteClicked(input, menuSpriteIDs[CREDITS]))
			{
				currentState = STATE_CREDIT;
			}
		}
	}

<<<<<<< HEAD
	void updateScore()
	{
		wchar_t scoreTxt[256];
		swprintf(scoreTxt, 256, L"Point(s): %i", currPoint);
	}

=======
>>>>>>> origin/master
	void updateGame() {
		int healthSize = getMaxHealth();
		int currAmmo = getMissileAmmo();

		// tells graphics what to draw
		GFX->addToSpriteRenderList((int*)gameSpriteIDs[0], gameSpriteIDs.size());

		// update health bar and number of missiles

		//Health bar update
		if(getMaxHealth() > getHealth()) // if current health is less than maximum health
		{
			for(healthSize; healthSize > getHealth(); --healthSize) //reduce the health bar size from the difference.
			{
				GFX->updateSprite(gameSpriteIDs.at(HEALTH), D3DXVECTOR3(350, 400, 0.0f)); // update the information
			}
		}
		
		//Missle Bar Update
		if(currAmmo < getMissileAmmo()) // if current ammo is less than its maximum supply
		{
			GFX->updateSprite(gameSpriteIDs.at(MISSILE), D3DXVECTOR3(310, 400, 0.0f)); //update the information
		}
		

		// Main has getHealth(), getMaxHealth(), and getMissileAmmo() functions that we can use. \
		   They've also provided me with their code. I haven't uploaded it, but if you want to \
		   see it, let me know.
		
	}
	void updatePause(const bool paused) {
		if (paused)
		{
			GFX->addToSpriteRenderList((int*)pauseSpriteIDs[0], pauseSpriteIDs.size());
			if (spriteClicked(input, pauseSpriteIDs[BACK]))
			{
				paused = false;
			}
		}
	}
	void updateExit() {
		// tell Graphics which sprites to draw
		GFX->addToSpriteRenderList((int*)exitSpriteIDs[0], exitSpriteIDs.size());
		currentState = STATE_EXIT;
	}


};