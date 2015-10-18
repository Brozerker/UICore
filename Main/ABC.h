/* ABC class created by Sam Rivera and further edited by Darrell Smith */

#pragma once

//d3d includes and libraries
#include "D3DUtils.h"
#include "physics.h"

namespace GSP420
{
	enum ObjType {
		OT_BEGIN = -1,
		OT_LARGE_ASTEROID,
		OT_SMALL_ASTEROID,
		OT_ENEMY1,
		OT_ENEMY2,
		OT_ENEMY3,
		OT_ENEMYBOSS,
		OT_PICKUP,
		OT_PLAYER_BULLET,
		OT_ENEMY_BULLET,
		OT_PLAYER_MISSILE,
		OT_ENEMY_MISSILE,
		OT_PLAYER,
		OT_END
	};

	class ABC
	{
	public:
		inline ABC();
		inline ABC(const ObjType t);
		inline ABC(const D3DXVECTOR3 p, const ObjType t);
		inline ABC(const D3DXVECTOR3 p, const D3DXVECTOR3 v, const ObjType t);
		inline ABC(const D3DXVECTOR3 p, const int h, const ObjType t);
		inline ABC(const D3DXVECTOR3 p, const D3DXVECTOR3 v, const int h, const ObjType t);

		virtual inline bool init(const int modelId, const int textureId);
		virtual inline void update(const float dt);
		virtual inline void shutdown();

		inline physicsObject& getPhys();
		inline int getHealth();
		inline int getModelId();
		inline int getTextureId();
		inline ObjType getObjectType();
		inline bool isEnabled();
		inline void setPosition(const D3DXVECTOR3& pos);
		inline void setVelocity(const D3DXVECTOR3& velo);
		inline void setFixedRotation(const D3DXVECTOR3& rot);
		inline void setHealth(const int health);
		inline void toggleEnabled();
		inline void setEnabled(const bool enabled);
		inline void setObjectType(ObjType t);

		inline const D3DXVECTOR3& getPosition() const;
		inline const D3DXVECTOR3& getVelocity() const;
		inline const D3DXVECTOR3& getFixedRotation() const;
		inline const D3DXVECTOR3& getScale() const;
		inline int getModelId() const;
		inline int getTextureId() const;
		//ABC(const ABC&);
		virtual inline ~ABC();

		physicsObject			physObj;
	protected:
		D3DXVECTOR3		position;
		D3DXVECTOR3		velocity;
		D3DXVECTOR3		fixedRotation;
		D3DXVECTOR3		scale;


		ObjType		eType;

		int		nHealth;
		int		nTextureId;
		int		nModelId;
		int		nObjectId;

		bool	bEnabled;
	};

	GSP420::ABC::ABC() : 
		bEnabled(true), 
		position(0.0f, 0.0f, 0.0f), 
		scale(1.0f, 1.0f, 1.0f), 
		velocity(0.0f, 0.0f, 0.0f), 
		fixedRotation(0.0f, 0.0f, 0.0f) 
	{
		//pPhysObj = new physicsObject();
	}
	GSP420::ABC::ABC(const ObjType t) : 
		eType(t), 
		bEnabled(true),
		position(0.0f, 0.0f, 0.0f), 
		scale(1.0f, 1.0f, 1.0f), 
		velocity(0.0f, 0.0f, 0.0f), 
		fixedRotation(0.0f, 0.0f, 0.0f) 
	{
		//pPhysObj = new physicsObject();
	}
	GSP420::ABC::ABC(const D3DXVECTOR3 p, const ObjType t) :
		position(p), 
		eType(t), 
		bEnabled(true), 
		scale(1.0f, 1.0f, 1.0f), 
		velocity(0.0f, 0.0f, 0.0f), 
		fixedRotation(0.0f, 0.0f, 0.0f) 
	{
		//pPhysObj = new physicsObject();
	}
	GSP420::ABC::ABC(const D3DXVECTOR3 p, const D3DXVECTOR3 v, const ObjType t) :
		position(p),
		velocity(v), 
		eType(t),
		bEnabled(true), 
		scale(1.0f, 1.0f, 1.0f), 
		fixedRotation(0.0f, 0.0f, 0.0f) 
	{
		//pPhysObj = new physicsObject();
	}
	GSP420::ABC::ABC(const D3DXVECTOR3 p, const int h, const ObjType t) :
		position(p), 
		velocity(D3DXVECTOR3(0.f, 0.f, 0.f)), 
		nHealth(h), 
		eType(t), 
		bEnabled(true), 
		scale(1.0f, 1.0f, 1.0f), 
		fixedRotation(0.0f, 0.0f, 0.0f) 
	{
	//	pPhysObj = new physicsObject();
	}
	GSP420::ABC::ABC(const D3DXVECTOR3 p, const D3DXVECTOR3 v, const int h, const ObjType t) :
		position(p), 
		velocity(v), 
		nHealth(h), 
		eType(t), 
		bEnabled(true), 
		scale(1.0f, 1.0f, 1.0f), 
		fixedRotation(0.0f, 0.0f, 0.0f) 
	{
	//	pPhysObj = new physicsObject();
	}

	GSP420::ABC::~ABC()
	{
// 		if (pPhysObj) {
// 			delete pPhysObj;
// 			pPhysObj = NULL;
// 		}
	}

	bool GSP420::ABC::init(const int modelId, const int textureId)
	{
		nModelId = modelId;
		nTextureId = textureId;
		physObj = physicsObject();
		return true;
	}
	void GSP420::ABC::update(const float dt) 
	{
		position.x = physObj.x + physObj.linearVelocityX * dt;
		position.y = physObj.y + physObj.linearVelocityY * dt;
	}
	void GSP420::ABC::shutdown() 
	{
// 		if (pPhysObj) {
// 			delete pPhysObj;
// 			pPhysObj = NULL;
// 		}
	}

	physicsObject& GSP420::ABC::getPhys()		{ return physObj; }

	const D3DXVECTOR3& GSP420::ABC::getPosition() const	{ return position; }
	const D3DXVECTOR3& GSP420::ABC::getVelocity() const { return velocity; }
	const D3DXVECTOR3& GSP420::ABC::getFixedRotation() const { return fixedRotation; }
	const D3DXVECTOR3& GSP420::ABC::getScale() const { return scale; }

	int GSP420::ABC::getModelId() const	{ return nModelId; }
	int GSP420::ABC::getTextureId() const { return nTextureId; }
	int GSP420::ABC::getHealth() { return nHealth; }
	int GSP420::ABC::getModelId() { return nModelId; }
	int GSP420::ABC::getTextureId() { return nTextureId; }
	ObjType GSP420::ABC::getObjectType() { return eType; }
	bool GSP420::ABC::isEnabled() { return bEnabled; }

	void GSP420::ABC::setPosition(const D3DXVECTOR3& pos) { position = pos; }
	void GSP420::ABC::setVelocity(const D3DXVECTOR3& velo) { velocity = velo; }
	void GSP420::ABC::setFixedRotation(const D3DXVECTOR3& rot) { fixedRotation = rot; }
	void GSP420::ABC::setHealth(const int health) { nHealth = health; }
	void GSP420::ABC::toggleEnabled() { bEnabled = !bEnabled; }
	void GSP420::ABC::setEnabled(const bool enabled) { bEnabled = enabled; }
	void GSP420::ABC::setObjectType(ObjType t) { eType = t; }
}