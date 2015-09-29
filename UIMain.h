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


/* -------- Williams's Additions ----------- */
#include "From Bill\UISpriteAnimation.h"
#include "From Bill\libraries.h"


typedef list<CSprite> SPRITELIST;

SPRITELIST				SPRITE_LIST;
SPRITELIST::iterator	SPRITE_A;
SPRITELIST::iterator	SPRITE_B;
SPRITELIST::iterator	SPRITE_C;

void    InitializeSprites(void);
void    ShipScore(void);

int   SCORE_BOARD       = 0;
int   HEALTH_BAR		= 9;
/* ---------------------------------------- */

class UIMain {
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
			updatePause();
		}
	}

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
	void updateGame() {
		// tells graphics what to draw
		GFX->addToSpriteRenderList((int*)gameSpriteIDs[0], gameSpriteIDs.size());

		// update health bar and number of missiles
		// Main has getHealth(), getMaxHealth(), and getMissileAmmo() functions that we can use. \
		   They've also provided me with their code. I haven't uploaded it, but if you want to \
		   see it, let me know.
	}
	void updatePause(const bool paused) {
		// tells graphics what to draw
		//currentSpritesToRender.push_back(PAUSED);
		//currentSpritesToRender.push_back(BACK);
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


/* -------- Williams's Additions ----------- */
void InitializeSprites(void)
{
    CSprite sprite;
    int i = 0;

	//RED HEALTH (FIRST)
    sprite.zeroSpriteValues();
    wcscpy_s( sprite.m_spriteType, L"redHP" );
    wcscpy_s( sprite.m_textureName, L"misc.bmp" );
    sprite.m_spriteW				= 200;
    sprite.m_spriteH				= 200;
    sprite.m_isActive				= false;
    sprite.m_oneFrame				= true;
    sprite.m_offsetX				= 51;
    sprite.m_offsetY				= 0;
    sprite.m_frameW					= 30;
    sprite.m_frameH					= 40;

    SPRITE_LIST.push_back(sprite);

	//YELLOW HEALTH (SECOND)
    sprite.zeroSpriteValues();
    wcscpy_s( sprite.m_spriteType, L"yellowHP" );
    wcscpy_s( sprite.m_textureName, L"misc.bmp" );
    sprite.m_spriteW				= 200;
    sprite.m_spriteH				= 200;
    sprite.m_isActive				= false;
    sprite.m_oneFrame				= true;
    sprite.m_offsetX				= 81;
    sprite.m_offsetY				= 0;
    sprite.m_frameW					= 30;
    sprite.m_frameH					= 40;
    
    SPRITE_LIST.push_back(sprite);

	//GREEN HEALTH (THIRD)
    sprite.zeroSpriteValues();
    wcscpy_s( sprite.m_spriteType, L"greenHP" );
    wcscpy_s( sprite.m_textureName, L"misc.bmp" );
    sprite.m_spriteW				= 200;
    sprite.m_spriteH				= 200;
    sprite.m_isActive				= false;
    sprite.m_oneFrame				= true;
    sprite.m_offsetX				= 111;
    sprite.m_offsetY				= 0;
    sprite.m_frameW					= 30;
    sprite.m_frameH					= 40;

    SPRITE_LIST.push_back(sprite);

	//SCORE NUMBER FONT
    for( i = 0; i < 4; i++ )
    {
        sprite.zeroSpriteValues();
        wcscpy_s( sprite.m_spriteType, L"numbers" );
        wcscpy_s( sprite.m_textureName, L"numbers.bmp" );
        sprite.m_spriteW             = 185;
        sprite.m_spriteH             = 27;
        sprite.m_State			     = i;
        sprite.m_posX				 = (float)600 + (i * 17);
        sprite.m_posY				 = 572;
        sprite.m_frameAnimate        = false;
        sprite.m_offsetX			 =  9;
        sprite.m_offsetY			 =  5;
        sprite.m_frameAcross         = 10;
        sprite.m_frameW				 = 17;
        sprite.m_frameH				 = 17;
        sprite.loadAnimationString( 0, "0 1 2 3 4 5 6 7 8 9", CSprite::LOOP_ANIMATION );

        SPRITE_LIST.push_back(sprite);
    }
}

void ShipScore(void)
{

	int number4 = SCORE_BOARD % 10; 
    int number3 = (SCORE_BOARD % 100)/10;
    int number2 = (SCORE_BOARD % 1000)/100;
    int number1 = (SCORE_BOARD % 10000)/1000;

    for( SPRITE_A = SPRITE_LIST.begin(); SPRITE_A != SPRITE_LIST.end(); ++SPRITE_A )
    {
        if( !lstrcmp(SPRITE_A->m_spriteType, L"numbers") )
        {
            if( SPRITE_A->m_State == 0 )
                SPRITE_A->m_CurrFrame = number1;

            if( SPRITE_A->m_State == 1 )
                SPRITE_A->m_CurrFrame = number2;

            if( SPRITE_A->m_State == 2 )
                SPRITE_A->m_CurrFrame = number3;

            if( SPRITE_A->m_State == 3 )
                SPRITE_A->m_CurrFrame = number4;
        }

    }
}
/* ---------------------------------------- */