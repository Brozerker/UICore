#pragma comment(lib, "SDL2")
#pragma comment(lib, "SDL2main")
#pragma comment(lib, "Physics")

#include <iostream> 
#include <SDL.h>
//#include <SDL2_image.h>
#include <string> 
#include <cmath>
#include "physics.h"

//Screen dimension constants
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;


//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//Loads individual image as texture
SDL_Texture* loadTexture(std::string path);

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

void OnCollission(void*, void*);


bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printf("Warning: Linear texture filtering not enabled!");
		}

		//Create window
		gWindow = SDL_CreateWindow("Physics Core Demo", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//Create renderer for window
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
			if (gRenderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor(gRenderer, 0xCC, 0xCC, 0xFF, 0xFF);

			/*	//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					success = false;
				} */

			}
		}
	}

	return success;
}

bool loadMedia()
{
	//Loading success flag
	bool success = true;

	//Nothing to load
	return success;
}

void close()
{
	//Destroy window	
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
//	IMG_Quit();
	SDL_Quit();
}

/*
SDL_Texture* loadTexture(std::string path)
{
	//The final texture
	//SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
		if (newTexture == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	return newTexture;
}

*/


void OnCollission(void* obj1, void* obj2) {
	std::cout << "Collission occured" << std::endl; 
	if (obj1 != NULL) {
		physicsObject* theObject1 = (physicsObject*) obj1;
		std::cout << "1:" << theObject1->objectName << std::endl;
	}

	if (obj2 != NULL) {
		physicsObject* theObject2 = (physicsObject*) obj2;
		std::cout << "2:" << theObject2->objectName << std::endl;
	}

}


int main(int argc, char *argv[]) {



	bool done = false; 
	int loopCount = 0; 

	
	// Create an Instance of Physics
	physics* Physics; 

	Physics = new physics(); 

	

	// Set up and few Objects to simulate 

	physicsObject* Box02;  

	Box02 = new physicsObject(); 

	
	Physics->GameObjectManager->addBoxDynamicRigidBody("Box02",400, 250,10,10,true, Box02);

	
	physicsObject* rectangle;

	rectangle = new physicsObject();


	Physics->GameObjectManager->addBoxDynamicRigidBody("getmyrectangle", 350, 100, 50, 25, true, rectangle);



	
	physicsObject* Box01;

	Box01 = new physicsObject();

	Physics->GameObjectManager->addBoxNonDynamicRigidBody("Box01",300, 400, 40, 300 , true, Box01);


	physicsObject* Box03;

	Box03 = new physicsObject();

	Physics->GameObjectManager->addBoxDynamicRigidBody("Box03", 400, 50, 10, 10, true, Box03);
	
	//std::vector<float32> myShape = { 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f };
	//Physics->GameObjectManager->addPolygonDynamicRigidBody("Box03", 400, 50, myShape, true, Box03);


	

	// Start the world simulating.  

	

	Physics->startWorld();
	
	Physics->collissionCallBackListener.setCollisionFunction(OnCollission);

	//Start up SDL and create window
	if (!init())
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		//Load media
		if (!loadMedia())
		{
			printf("Failed to load media!\n");
		}
		else
		{
			//Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event e;

			//While application is running
			while (!quit)
			{
				//Handle events on queue
				while (SDL_PollEvent(&e) != 0)
				{
					//User requests quit
					if (e.type == SDL_QUIT)
					{
						quit = true;
					}


					if (e.type == SDL_KEYDOWN)
					{
						switch (e.key.keysym.sym){
						case SDLK_RIGHT:
							Box02->applyForceFromCenter(0, -1);
							break;

						case SDLK_LEFT:
							Box01->applyForceFromCenter(-1.0f, 0);
							break;

						case SDLK_SPACE:
							Box01->applyForceFromCenter(0, -10);
							break;

						case SDLK_t:
							Box01->applyImpulseFromCenter(0, -20);
							break;

						case SDLK_b:
							Box01->setBounceAmount(0.0098f);
							break;


						}
					}



				}


				//Update screen
				Physics->updateWorld(1.0f);

			

				//Clear screen
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear(gRenderer);



				
				//printf("%4.2f %4.2f %4.2f\n",Box01->x*M2P, Box01->y*M2P, Box01->angle);



				//Render red filled quad
				SDL_Rect fillRect = { Box01->x, Box01->y, Box01->halfHeight * 2,   Box01->halfWidth * 2};

				SDL_Rect fillRect2 = { Box02->x, Box02->y, Box02->halfHeight * 2,Box02->halfWidth * 2 };

				SDL_Rect fillRect3 = { rectangle->x, rectangle->y, rectangle->halfHeight * 2, rectangle->halfWidth * 2 };

				SDL_Rect fillRect4 = { Box03->x, Box03->y, Box03->halfHeight * 2, Box03->halfWidth * 2 };



				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0x00, 0xFF);
				
				SDL_RenderFillRect(gRenderer, &fillRect);

				
				SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0xFF, 0xFF);

				SDL_RenderFillRect(gRenderer, &fillRect2);

					
			
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0x00, 0xFF);

				SDL_RenderFillRect(gRenderer, &fillRect3);
				
				
				SDL_SetRenderDrawColor(gRenderer, 0x00, 0xFF, 0x00, 0xFF);
				SDL_RenderFillRect(gRenderer, &fillRect4);

				

			
				

			


				SDL_RenderPresent(gRenderer);
			}
		}
	}


	

	Physics->endWorld(); // we are done end the world. 
	
	


	return 0; 
}

