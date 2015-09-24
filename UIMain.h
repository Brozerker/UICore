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
using namespace std;


class UIMain {
	GAMESTATE currentState;
	GFXCore::Graphics gfx;
	// Stores the position of sprites that LoadSprite loads into an array so that they can be accessed later
	vector<int> spriteElementPositions; 
	vector<int> currentSpritesToRender;
	int currentScore;
	int missileAmmo;
public:

	UIMain(): currentState(STATE_INIT), currentScore(0), missileAmmo(0) {}
	~UIMain();

	void init() {
		spriteElementPositions[0] = gfx.loadSprite((wchar_t*)"Sprites\Background.png");
		spriteElementPositions[1] = gfx.loadSprite((wchar_t*)"Sprites\Title.png", D3DXVECTOR3(300, 100, 0.0f));
		spriteElementPositions[2] = gfx.loadSprite((wchar_t*)"Sprites\Start.png", D3DXVECTOR3(350, 300, 0.0f));
		spriteElementPositions[3] = gfx.loadSprite((wchar_t*)"Sprites\Credits.png", D3DXVECTOR3(350, 400, 0.0f));
		spriteElementPositions[4] = gfx.loadSprite((wchar_t*)"Sprites\missile.png");
		spriteElementPositions[5] = gfx.loadSprite((wchar_t*)"Sprites\healthBackground.png");
		spriteElementPositions[6] = gfx.loadSprite((wchar_t*)"Sprites\healthBar.png");
		spriteElementPositions[7] = gfx.loadSprite((wchar_t*)"Sprites\Paused.png", D3DXVECTOR3(300, 100, 0.0f));
		spriteElementPositions[8] = gfx.loadSprite((wchar_t*)"Sprites\Back.png", D3DXVECTOR3(350, 400, 0.0f));
	}

	GAMESTATE checkStateChanges() {
		return currentState;
	}

	void update(const float dt, const GAMESTATE state, const bool paused) {
		currentState = state;
		if (!paused) {
			switch(state) {
			case STATE_MENU:
				updateMenu();
				break;
			case STATE_PLAY:
				updateGame();
				break;
			case STATE_EXIT:
				updateExit();
				break;
			}
		} else {
			// TODO: elliminate updatePause and just call updateMenu() using different sprites
			updatePause();
		}
	}

	void updateMenu() {
		currentSpritesToRender.clear();
		currentSpritesToRender.push_back(BACKGROUND);
		currentSpritesToRender.push_back(TITLE);
		currentSpritesToRender.push_back(START);
		currentSpritesToRender.push_back(CREDITS);
		// tell Graphics which sprites to draw (0,1,2,3)
		// check for mouse input
		// for each button
			// was mouse input within button?
			// change currentState accordingly
	}
	void updateGame() {
		currentSpritesToRender.clear();
		currentSpritesToRender.push_back(BACKGROUND);
		currentSpritesToRender.push_back(MISSILE);
		currentSpritesToRender.push_back(HPBACKGROUND);
		currentSpritesToRender.push_back(HEALTH);
		// tell Graphics which sprites to draw (0, 4, 5, 6)
		// update health bar and number of missiles
		// Main has getHealth(), getMaxHealth(), and getMissileAmmo() functions that we can use. \
		   They've also provided me with their code. I haven't uploaded it, but if you want to \
		   see it, let me know.
	}
	void updatePause() {
		currentSpritesToRender.push_back(PAUSED);
		currentSpritesToRender.push_back(BACK);
		// tell Graphics which sprites to draw (7,8)
		// check for mouse input
		// was button pressed?
			// change currentState accordingly
	}
	void updateExit() {
		// tell Graphics which sprites to draw
		// Display game over sprite or something
	}
};