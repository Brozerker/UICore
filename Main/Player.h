//Player class created by Darrell Smith and edited by Brent Spector

#pragma once

#include "ABC.h"


//keeping the score amounts in one place to make them easier to alter
const static int ENEMY_1_SCORE = 15;
const static int ENEMY_2_SCORE = 25;
const static int ENEMY_3_SCORE = 50;
const static int ENEMY_BOSS_SCORE = 250;
const static int ASTEROID_SMALL_SCORE = 20;
const static int ASTEROID_LARGE_SCORE = 20;
const static float BULLET_COOL_DOWN = .5f;
const static D3DXVECTOR3 BULLET_START_DIRECTION = D3DXVECTOR3(0.f, 1.f, 0.f);
const static float MISSILE_COOL_DOWN = 1.f;
const static float PLAYER_SPEED = 200.f;


const static float HURT_INVULNERABILITY = 1.f;//how long player is invulnerable after being harmed

class Player : public GSP420::ABC
{
public:
	inline Player();
	void fireBullet();
	void resetBulletTime() { lastBullet = 0.0f; }
	void fireMissile();
	void heal(int);
	void hurt(int);
	void move(D3DXVECTOR3);
	void endGame();
	void update(const float);
	void shutdown();

	inline int getMissileAmmo();
	inline int getMaxHealth();
	inline void giveScore(int s);
	void makeInvulnerable(float secs);
	inline void giveMissileAmmo(int ammo);
	inline int getScore();
private:
	int missileAmmo;
	int maxHealth;
	int score;
	float invulnerable;//seconds of invulnerability left
	float lastBullet;//if <= 0, player can fire a bullet
	float lastMissile;//if <=0, player can fire a missile
};
// TODO: change missile ammo back to 0, for testing only
Player::Player() : 
GSP420::ABC(),
missileAmmo(5),
maxHealth(25), 
invulnerable(0.f), 
score(0),
lastBullet(0.f), 
lastMissile(0.f)
{
	nHealth = 25;
}

int Player::getMissileAmmo() { return missileAmmo; }
int Player::getMaxHealth() { return maxHealth; }
void Player::giveScore(int s) { score += s; }
void Player::giveMissileAmmo(int ammo) { missileAmmo += ammo; }
int Player::getScore() { return score; }