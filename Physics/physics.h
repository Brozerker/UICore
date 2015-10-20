#pragma once 
#include <iostream>
#include <vector> 
#include "gameObjectManager.h"
#include "Box2D/Box2D.h"
//#pragma warning(disable : 4006)
#pragma comment(lib, "Box2d")
const float M2P = 8.00;
const float P2M = 1 / M2P;

enum gameObjectCollissionCategory{
	gocBOUNDARY      = 0x0001,
	gocPLAYER        = 0x0002,
	gocMISSLE        = 0x0004,
	gocPICKUP        = 0x0008,
	gocENEMY         = 0x0010
};

class CollissionCallBackListener : public b2ContactListener
{

 public: 
	void (*listenerParentCallbackFunction)(void*,void*);
	void CollissionCallBackListener::BeginContact(b2Contact* contact);
	void EndContact(b2Contact* contact);
	void setCollisionFunction(void (*theParentCollisionFunction)(void*, void*) );
};

class physics 
{
public:
	
	b2Vec2 gravity; 
    b2World* world;
	CollissionCallBackListener collissionCallBackListener; 
	b2BodyDef groundBodyDef;
	b2PolygonShape groundBox;
	
	
	float32 timeStep = 1.0f / 30.0f;
	const int32 velocityIterations = 10;
	const int32 positionIterations = 6;

	physics();

	physics(float32 gravityX, float32 gravityY);

	~physics();

	gameObjectManager* GameObjectManager; 

	// 
	//int onStartCollission(void* object1, void* object2);
	//int onEndCollission(void* object1, void* object2);

	// clean up and get rid of any traces of our world phyiscs world
	int endWorld();
	// create and Instance of the physics world 
	int startWorld();
	// update the simulation by calling this in the main loop.
	int updateWorld(float dt);
};






