//Who needs what?
//Main:
//	update functions
//	gamestate change
//Graphics:
//	position & filename of sprites
//Physics:
//	Size & position of buttons

#include "From Main/GameState.h"
#include "UIButton.h"
class UIMain {
public:
	void activateButton(UIButton button);
	void setGameState(GAMESTATE newState);
	GAMESTATE getGameState();
	void update();
	void updateMenu();
	void updateGame();
	// void updateCredits(); Are the credits UI?
};