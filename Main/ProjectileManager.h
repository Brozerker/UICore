//Projectile Manager, Bullet, and Missile classes created by Darrell Smith and Brent Spector
#pragma once

#include <list>
#include "ABC.h"
#include "EnemyManager.h"


static const int BULLET_DAMAGE = 1;
static const int MISSILE_DAMAGE = 2;
static const int COLLISION_DAMAGE = 1;
static const int MISSILE_RADIUS = 50;

const static float BULLET_SPEED = 50.f;
const static float MISSILE_SPEED = 40.f;

class Bullet : public GSP420::ABC
{
public:
	Bullet(const D3DXVECTOR3 pos, const D3DXVECTOR3 vel, const ObjType t) : ABC(pos, vel, t) {}
	void update(const float) {}
	bool init(const int modelId, const int textureId) { this->nModelId = modelId; this->nTextureId = textureId; return true; }
	void shutdown() {}
	inline bool isPlayers() { return eType == OT_PLAYER_BULLET; }
protected:
};

class Missile : public GSP420::ABC
{
public:
	//initial velocity is 0 because that will be set after it's target is set
	Missile(const D3DXVECTOR3 pos, const ObjType t, Enemy* targ = NULL) :
		ABC(pos, D3DXVECTOR3(0.f, 0.f, 0.f), t), target(targ)
	{}
	void update(const float) {}
	//bool init(const int modelId, const int textureId) { return true; }
	void shutdown() {}
	inline void setEnemyTarget(Enemy*e) { target = e; }
	inline Enemy* getEnemyTarget() { return target; }//returns NULL if it needs re-targeted or if player is target
	inline bool isPlayers() { return eType == OT_PLAYER_MISSILE; }
private:
	Enemy* target;//applies only to player's missiles, will be null if it is player's or if it needs re-targeted
};

class ProjectileManager
{
	friend class AI;
	friend class D3DCore;
	friend class Physics;
public:
	void initBulletProjectiles(const int modelId, const int textureId);
	void initMissileProjectiles(const int modelId, const int textureId);
	inline void addBullet(Bullet b) { Bullets.push_front(b); }
	inline void addMissile(Missile m) { Missiles.push_front(m); }
	void update(const float);
	inline void clear() { Bullets.clear(); Missiles.clear(); }
	void removeTarget(Enemy*);//if any missiles are targeting that enemy, set their targets to NULL instead
	const std::list<Bullet>& getBullets() const { return Bullets; }

	ProjectileManager() :
		nMissileModelId(-1),
		nBulletTextureId(-1),
		nBulletModelId(-1),
		nMissileTextureId(-1)
	{}
private:
	inline std::list<Bullet>& getBullets() { return Bullets; }
	std::list<Bullet> Bullets;
	inline std::list<Missile>& getMissiles() { return Missiles; }
	std::list<Missile> Missiles;

	int nBulletModelId;
	int nBulletTextureId;
	int nMissileModelId;
	int nMissileTextureId;
};
