#include "UIMain.h"

class UI_Interface : UIMain {
public:
	void init() {
		menuSpriteIDs.push_back(GFX->loadSprite((wchar_t*)"Sprites\Background.png"));
		menuSpriteIDs.push_back(GFX->loadSprite((wchar_t*)"Sprites\Title.png", D3DXVECTOR3(300, 100, 0.0f)));
		menuSpriteIDs.push_back(GFX->loadSprite((wchar_t*)"Sprites\Start.png", D3DXVECTOR3(350, 300, 0.0f)));
		menuSpriteIDs.push_back(GFX->loadSprite((wchar_t*)"Sprites\Credits.png", D3DXVECTOR3(350, 400, 0.0f)));
		gameSpriteIDs.push_back(GFX->loadSprite((wchar_t*)"Sprites\missile.png"));
		gameSpriteIDs.push_back(GFX->loadSprite((wchar_t*)"Sprites\healthBackground.png"));
		gameSpriteIDs.push_back(GFX->loadSprite((wchar_t*)"Sprites\healthBar.png"));
		pauseSpriteIDs.push_back(GFX->loadSprite((wchar_t*)"Sprites\Paused.png", D3DXVECTOR3(300, 100, 0.0f)));
		pauseSpriteIDs.push_back(GFX->loadSprite((wchar_t*)"Sprites\Back.png", D3DXVECTOR3(350, 400, 0.0f)));
		exitSpriteIDs.push_back(GFX->loadSprite((wchar_t*)"Sprites\Gameover.png", D3DXVECTOR3(0.0f, 0.0f, 0.0f)));
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
			//updatePause();
		}
	}
};