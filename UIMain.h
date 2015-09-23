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

// Sprite order
#define HELP 0


class UIMain {
	GAMESTATE currentState;
	GFXCore::Graphics gfx;
	// Stores the position of sprites that LoadSprite loads into an array so that they can be accessed later
	int * spriteElementPositions; 
	int currentScore;
	int missileAmmo;
public:

	//UIMain(): currentState(STATE_INIT), currentScore(0), missileAmmo(0) {}
	//~UIMain();

	void init() {
		//spriteElementPositions[0] = gfx.loadSprite("background.png");
		//spriteElementPositions[1] = gfx.loadSprite("title.png");
		//spriteElementPositions[2] = gfx.loadSprite("play.png");
		//spriteElementPositions[3] = gfx.loadSprite("credits.png");
		//spriteElementPositions[4] = gfx.loadSprite("quit.png");
		//spriteElementPositions[5] = gfx.loadSprite("missile.png");
		//spriteElementPositions[6] = gfx.loadSprite("healthBackground.png");
		//spriteElementPositions[7] = gfx.loadSprite("healthBar.png");
		//spriteElementPositions[8] = gfx.loadSprite("back.png");
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
		// tell Graphics which sprites to draw
		// check for mouse input
		// for each button
			// was mouse input within button?
			// change currentState accordingly
	}
	void updateGame() {
		// tell Graphics which sprites to draw
		// update health bar and number of missiles
		// Main has getHealth(), getMaxHealth(), and getMissileAmmo() functions that we can use. \
		   They've also provided me with their code. I haven't uploaded it, but if you want to \
		   see it, let me know.
	}
	void updatePause() {
		// tell Graphics which sprites to draw
		// check for mouse input
		// was button pressed?
			// change currentState accordingly
	}
	void updateExit() {
		// tell Graphics which sprites to draw
		// Display game over sprite or something
	}
};