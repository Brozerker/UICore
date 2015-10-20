#include "physicsObject.h"


physicsObject::physicsObject() 
{ 
 
	body      = NULL; 
    userData  = NULL; 
	collissionCategory = 0; //Im a thing
	collissionMask = 0;     // I collide with everything.
}


physicsObject::~physicsObject()
{
}


// turn on the object to react in phyiscs world
int physicsObject::activate()
{
	return 0;
}


// turn off the physics object but not remove it. It will not react to physics or collisions
int physicsObject::deactivate()
{
	return 0;
}


// remove this object from the game manager. This is  stub method that will call the gameManagers remove method
int physicsObject::remove()
{
	return 0;
}

//applies force from the center of an object
int physicsObject::applyForceFromCenter(float32 x, float32 y)
{
	b2Vec2 theforce(x, y); 
	body->ApplyForce(theforce, body->GetWorldCenter(), true);
	return 0;
}

//applies force from the center of an object
int physicsObject::applyImpulseFromCenter(float32 x, float32 y)
{
	b2Vec2 theforce(x, y);
	body->ApplyLinearImpulse(theforce, body->GetWorldCenter(), true);
	return 0;
}

//applies force from the center of an object
int physicsObject::applyTorqueFromCenter(float32 rotation)
{
	b2Vec2 theforce(rotation, y);
	body->ApplyTorque(rotation, true);
	return 0;
}


int physicsObject::setLinkedObject(void* linkedObject)
{
	userData = &linkedObject;
	if (linkedObject != NULL) {
		body->SetUserData(&userData);
	}
	return 0;
}

int physicsObject::setBounceAmount(float32 ba)
{
	bounceAmount = ba; // track locally for convenience.
	body->GetFixtureList()->SetDensity(ba);
	body->ResetMassData();
	return 0;
}

int physicsObject::setCollissionMask(uint16 cm)
{
	collissionMask = cm; // track locally for convenience.
	//Can only be used when the object is created for the first time. 
	return 0;
}

int physicsObject::setCollissionCategory(uint16 cc)
{
	collissionCategory = cc; // track locally for convenience.

	//Can only be used when the object is created for the first time. 
	return 0;
}