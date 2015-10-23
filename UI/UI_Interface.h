#pragma once
#include "UIMain.h"

class UI_Interface : UIMain {
public:
	void init() {
		menuSpriteIDs.push_back(GFX->loadSprite(L"..\\EngineDemo\\Content\\Sprites\\thing.jpg", D3DXVECTOR3(0.0f,0.0f,0.0f)));
 		menuSpriteIDs.push_back(GFX->loadSprite(L"..\\EngineDemo\\Content\\Sprites\\Title.jpg", D3DXVECTOR3(300, 100, 0.0f)));
 		menuSpriteIDs.push_back(GFX->loadSprite(L"..\\EngineDemo\\Content\\Sprites\\Start.jpg", D3DXVECTOR3(350, 300, 0.0f)));
 		menuSpriteIDs.push_back(GFX->loadSprite(L"..\\EngineDemo\\Content\\Sprites\\Credits.jpg", D3DXVECTOR3(350, 400, 0.0f)));
		gameSpriteIDs.push_back(GFX->loadSprite(L"..\\EngineDemo\\Content\\Sprites\\missile.jpg", D3DXVECTOR3(300, 710, 0.0f)));
		gameSpriteIDs.push_back(GFX->loadSprite(L"..\\EngineDemo\\Content\\Sprites\\healthBackground.jpg", D3DXVECTOR3(370, 710, 0.0f)));
		gameSpriteIDs.push_back(GFX->loadSprite(L"..\\EngineDemo\\Content\\Sprites\\healthBar.jpg", D3DXVECTOR3(370, 710, 0.0f)));
 		//gameSpriteIDs.push_back(GFX->loadSprite(L"Content\\Sprites\\score.png"));
 		//pauseSpriteIDs.push_back(GFX->loadSprite(L"..\\EngineDemo\\Content\\Content\\Sprites\\Paused.jpg", D3DXVECTOR3(300, 100, 0.0f)));
 		//pauseSpriteIDs.push_back(GFX->loadSprite(L"..\\EngineDemo\\Content\\Content\\Sprites\\Back.jpg", D3DXVECTOR3(350, 400, 0.0f)));
		//exitSpriteIDs.push_back(GFX->loadSprite(L"..\\EngineDemo\\Content\\Content\\Sprites\\Gameover.jpg", D3DXVECTOR3(0.0f, 0.0f, 0.0f)));
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