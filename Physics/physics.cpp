#include "physics.h"
#include "physicsObject.h"



physics::physics(float32 gravityX, float32 gravityY) 
{

	gravity = b2Vec2(gravityX, gravityY); // need to expose gravtiy in constuctor.
	world = new b2World(gravity);
	GameObjectManager = new gameObjectManager();
}

 


physics::physics()
{
	
    gravity = b2Vec2(0.0f, -0.0f); // need to expose gravtiy in constuctor.
	world = new b2World(gravity);
	GameObjectManager = new gameObjectManager();
	
}


physics::~physics()
{ 
	delete GameObjectManager; 
	
}


// clean up and get rid of any traces of our world phyiscs world
int physics::endWorld()
{
	return 0;
}


// create and Instance of the physics world 
int physics::startWorld()
{
	world->SetContactListener(&collissionCallBackListener);

	return 0;
}


// update the simulation by calling this in the main loop.
int physics::updateWorld(float dt)
{
//	timeStep = dt;
	world->Step(timeStep, velocityIterations, positionIterations);

	// Lets Loop through and create all our objects.
	std::map<std::string, physicsObject*>::iterator gameObject;

	for (gameObject = GameObjectManager->gameManangerMap.begin(); gameObject != GameObjectManager->gameManangerMap.end(); gameObject++)
	{

		b2PolygonShape dynamicBox;

		if (gameObject->second->body == NULL) // Has the object been created yet ? If not create it. 

		{

			// Define the dynamic body. We set its position and call the body factory.

			b2BodyDef bodyDef;

		

			if (gameObject->second->isDynamic)  {
				bodyDef.type = b2_dynamicBody;
			}
			else {
				bodyDef.type = b2_kinematicBody;
			}

			// but if static change 

			if (gameObject->second->isStatic)  {
				bodyDef.type = b2_staticBody;
			}


			bodyDef.position.Set(P2M*gameObject->second->x, P2M*gameObject->second->y);


			
			b2Body* body = world->CreateBody(&bodyDef);
			
			body->SetUserData(gameObject->second);
				
			if (gameObject->second->shapeList == "Box") {
				dynamicBox.SetAsBox(P2M*gameObject->second->halfHeight, P2M*gameObject->second->halfWidth);
			}
			else // we can assume polygon for now unless we add circles later.
			{ 
				
				
				// count the vertices 
				int vertexCount = gameObject->second->shape.size() / 2;

				//convert to an array. 
				float32* verticeArray = &gameObject->second->shape[0];
			
			    //create a vector of b2vec2
				std::vector<b2Vec2> vertices;
				
				//init it
				vertices.resize(vertexCount);

				//stuff it with the vertices
				for (int loopIndex = 0; loopIndex < vertexCount; loopIndex++) {

					vertices[loopIndex].Set(verticeArray[loopIndex], verticeArray[loopIndex + 1]);

				}

				// flatten to an array
				b2Vec2* b2vArray = &vertices[0];

				//Yep I know it says box but it is a type of polygonshape.
				dynamicBox.Set(b2vArray, vertexCount); //pass array to the shape

			

				}
	

			b2FixtureDef fixtureDef;
			fixtureDef.shape = &dynamicBox;

			// Set the box density to be non-zero, so it will be dynamic.
			fixtureDef.density = 1.0f;

			fixtureDef.restitution = 0.949875f;

			// Override the default friction.
			fixtureDef.friction = 0.9800f;
			 
			if ((gameObject->second->collissionCategory != 0) && (gameObject->second->collissionMask != 0)) {
				fixtureDef.filter.categoryBits = gameObject->second->collissionCategory;
				fixtureDef.filter.maskBits = gameObject->second->collissionMask;
			} 
			// Add the shape to the body.
			body->CreateFixture(&fixtureDef);

			gameObject->second->body = body;



		}
		else  // need to update the objects information..
		{

			//*** To do ****
			//Need to check if object was added or removed after the world was created
			//and do create or remove it.

			b2Vec2 position = gameObject->second->body->GetPosition();
			gameObject->second->x = int(position.x*M2P);
			gameObject->second->y = int(position.y*M2P);
			float32 theAngle = gameObject->second->body->GetAngle();
			gameObject->second->angle = theAngle;

		}

		
	}




	return 0;
}


void CollissionCallBackListener::BeginContact(b2Contact* contact)
{
	b2Fixture* fixtureA = contact->GetFixtureA();
	b2Fixture* fixtureB = contact->GetFixtureB();
	b2Body* body1 = fixtureA->GetBody();
	b2Body* body2 = fixtureB->GetBody();
	//physicsObject* poA = (physicsObject*)body1->GetUserData();
	//physicsObject* poB = (physicsObject*)body2->GetUserData();

	 void* poA = (void*) body1->GetUserData();
	 void* poB = (void*) body2->GetUserData();
	 //if ((poA != NULL) && (poB != NULL)) {  // make sure data is attached
		 if (listenerParentCallbackFunction != NULL)  { // make sure there is a call back attached.
			 listenerParentCallbackFunction(poA, poB); //send the collided objects data to callback.
		// }
	 } 

}

void CollissionCallBackListener::EndContact(b2Contact* contact)
{
	//std::cout << "Collission ended" << std::endl;
}

void CollissionCallBackListener::setCollisionFunction(void(*theParentCollisionFunction)(void*, void*)) {
	listenerParentCallbackFunction = theParentCollisionFunction;
}
