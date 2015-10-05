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

static int		currHealth		= HEALTH;
static int		currAmmo		= MISSILE;
static int		currPoint		= 0;

float g_posX;
float g_posY;


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

	void updateScore()
	{
		wchar_t scoreTxt[256];
		swprintf(scoreTxt, 256, L"Point(s): %i", currPoint);
	}

	void updateGame() {
		float healthPosX = 300;
		float healthPosY = 100;

		float ammoPosX = 200;
		float ammoPosY = 100;

		

		// tells graphics what to draw
		GFX->addToSpriteRenderList((int*)gameSpriteIDs[0], gameSpriteIDs.size());

		// update health bar and number of missiles

		//Health bar update
		g_posX = healthPosX;
			if(HEALTH > currHealth)
			{
				for(int i = 0; i < currHealth; ++i)
				{
					GFX->updateSprite((wchar_t)"hp", D3DXVECTOR3(g_posX, healthPosY, 0.0f)); //update the next health bar node position

					//add printsprite() function to display the health
					
					g_posX + 10; // increase the distance from the previous health bar node to the next node.
				}
				g_posX = healthPosX; // reset x coord position
			}
		
		//Missle Bar Update
		GFX->updateSprite((wchar_t)"missles", D3DXVECTOR3( ammoPosX, ammoPosY, 0.0f ));

		//add printsprite() function to display the current ammo



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