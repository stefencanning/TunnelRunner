#define CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include "SDL.h"
#include <stdio.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <string>
#include <iostream>
#include <ctime>
#include "SDL_ttf.h"
#include "SDL_timer.h"
#include <vector>
#include "SceneManager.h"
#include "TextureManager.h"
#include "SoundManager.h"
#include <chrono>
#include <windows.h>
#include <fstream>

//Screen dimension constants 
//The window we'll be rendering to 
SDL_Window* window = nullptr; 
//Event handler 
SDL_Event eHandler;
//The window renderer 
SDL_Renderer* renderer = nullptr; 
//Current displayed texture 
SDL_Rect stretchRect; 

//Starts up SDL and creates window 
bool init(); 
//Loads media 
bool loadMedia(); 
//Frees media and shuts down SDL 
void close();
SDL_Texture* loadTexture( std::string path );

using namespace std;
using namespace std::chrono;



bool init() 
{ 
	//Initialization flag 
	bool success = true; 
	int screenWidth=1280;
	int screenHeight=720;
	stretchRect.x = 0; 
	stretchRect.y = 0; 
	stretchRect.w = screenWidth; 
	stretchRect.h = screenHeight;


	//Initialize SDL 
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) 
	{ 
		printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() ); 
		success = false; 
	} 
	else 
	{  
		if(SDL_Init(SDL_INIT_AUDIO) < 0)
		{
			printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() ); 
			success = false; 
		} 
		else 
		{  
			if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 1024 ) < 0 )
			{
				printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
				SoundManager::getManager()->sound = false;
			}

			//Set texture filtering to linear
			if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
			{
				printf( "Warning: Linear texture filtering not enabled!" );
			}
			window = SDL_CreateWindow( "Tunnel Runner", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenWidth, screenHeight, SDL_WINDOW_SHOWN ); 
			if( window == nullptr )
			{
				printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() ); 
				success = false; 
			} 
			else 
			{ 
				//Create renderer for window 
				renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED ); 
				if( renderer == nullptr ) 
				{ 
					printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() ); 
					success = false;
				} 
				else 
				{ 
					//Initialize renderer color 
					SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF ); 
					//Initialize PNG loading 
					int imgFlags = IMG_INIT_PNG; 
					if( !( IMG_Init( imgFlags ) & imgFlags  ) ) 
					{ 
						string a = IMG_GetError();
						printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
						success = false; 
					} 
				} 
			}
			//intialise truetype font for writing purposes
			if(TTF_Init() == -1)
			{
				return false;
			}
		}
	} 
	return success; 
}



SDL_Texture* loadTexture( std::string path ) 
{ 
	//The final texture 
	SDL_Texture* newTexture = nullptr; 
	//Load image at specified path 
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == nullptr ) 
	{ 
		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	} 
	else 
	{
		//Create texture from surface pixels 
		//newTexture = SDL_CreateTextureFromSurface( renderer, loadedSurface ); 
		newTexture = SDL_CreateTextureFromSurface( renderer, loadedSurface ); 
		if( newTexture == nullptr ) 
		{ 
			printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() ); 
		} 
		//Get rid of old loaded surface 
		SDL_FreeSurface( loadedSurface ); 
	} 
	return newTexture; 
}





void close() 
{ 
	//Free loaded image 
	//Destroy window 
	SDL_DestroyRenderer( renderer ); 
	SDL_DestroyWindow( window ); 
	window = nullptr; 
	renderer = nullptr; 
	//Quit SDL subsystems 
	IMG_Quit(); 
	SDL_Quit();

}


int main( int argc, char* args[] ) 
{ 
	bool QUIT = false;
	if( !init() )
	{ 
		printf( "Failed to initialize!\n" ); 
	} 
	else 
	{
		//milliseconds start = duration_cast< milliseconds >(high_resolution_clock::now().time_since_epoch());
		std::clock_t mClock;
		int min = 1000;
		mClock = std::clock();
		//Load media 
		if( !loadMedia() )	
		{
			printf( "Failed to load media!\n" );
		}
		else
		{
			srand (time(0));
			bool run = true;
			while(run)
			{

				//if(((std::clock()-mClock)/(double)CLOCKS_PER_SEC) >= 1.0/480.0)
				//milliseconds num =  duration_cast< milliseconds >(high_resolution_clock::now().time_since_epoch())-start;
				std::clock_t num = std::clock()-mClock;
				//float time = num.count()/1000.0f;
				float time = num/1000.0f;
				if(time >= 1.0f/60.0f)
				{
					//start = duration_cast< milliseconds >(high_resolution_clock::now().time_since_epoch());
					mClock = std::clock();
					KeyManager::getManager()->Update(eHandler);


					SceneManager::getManager()->update(time);
					SceneManager::getManager()->draw(renderer);
					if(KeyManager::getManager()->keyPressed(SDL_SCANCODE_ESCAPE)||KeyManager::getManager()->quit())
					{
						run=false;
					}
				}
			}
		}
	}
	delete KeyManager::getManager();
	delete ObjectManager::getManager();
	delete SceneManager::getManager();
	delete SoundManager::getManager();
	delete TextureManager::getManager();

	close();
	_CrtDumpMemoryLeaks();

	return 0;
}



bool loadMedia() 
{ 
	//Loading success flag 
	bool success = true; 
	//*
	//backgrounds
	TextureManager::getManager()->player = new Texture(renderer,"images/player.png");
	TextureManager::getManager()->wall = new Texture(renderer,"images/wall.png");
	TextureManager::getManager()->magma = new Texture(renderer,"images/magma.png");
	TextureManager::getManager()->lava = new Texture(renderer,"images/lava.png");
	TextureManager::getManager()->gold = new Texture(renderer,"images/gold.png");
	TextureManager::getManager()->bedrock = new Texture(renderer,"images/bedrock.png");
	TextureManager::getManager()->scoreScreen = new Texture(renderer,"images/score&distance.png");
	TextureManager::getManager()->water = new Texture(renderer,"images/water.png");
	TextureManager::getManager()->miners = new vector<Texture*>();
	for(int i = 1; i < 15; i++)
	{
		TextureManager::getManager()->miners->push_back(new Texture(renderer,"images/Miner ("+std::to_string(i)+").png"));
	}

	//font
	TextureManager::getManager()->font = TTF_OpenFont("images/BRIDGEB.ttf", 36);
	//TextureManager::getManager()->fontInner = TTF_OpenFont("images/fonts/BOOTERFZ.ttf", 30);
	//TextureManager::getManager()->fontText = TTF_OpenFont("images/fonts/BOOTERFZ.ttf", 18);

//	SoundManager::getManager()->shipSound
	//Sounds
	SoundManager::getManager()->loadSound();
	//*/
	return success; 
}