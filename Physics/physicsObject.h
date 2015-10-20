#pragma once

#include <string>
#include "Box2D/Box2D.h"
#include <vector>


class physicsObject
{
public:
	
	b2Body* body;
	std::string objectName;
	std::vector<float32> shape;
	float32 angle;
	float32 angularVelocityX; 
	float32 angularVelocityY; 
	float32 linearVelocityX;
	float32 linearVelocityY;
	float  bounceAmount; 
	float  friction; 
	bool   isActive;
	bool   isColliding; 
	bool   isDynamic;
	bool   isStatic; 
	int    x; 
	int    y; 
	int    halfHeight; 
	int    halfWidth; 
	std::string shapeList; 
	void* userData; 
	uint16 collissionMask; 
	uint16 collissionCategory;
	physicsObject();
	~physicsObject();
	// turn on the object to react in phyiscs world
	int activate();
	// turn off the physics object but not remove it. It will not react to physics or collisions
	int deactivate();
	// remove this object from the game manager. This is  stub method that will call the gameManagers remove method
	int remove();
	int applyForceFromCenter(float32 x, float32 y);
	int applyImpulseFromCenter(float32 x, float32 y);
	int applyTorqueFromCenter(float32 rotation);
	int setLinkedObject(void* linkedObject);
	int setBounceAmount(float32 ba);
	int setCollissionMask(uint16 cm);
	int setCollissionCategory(uint16 cc);
	
};

