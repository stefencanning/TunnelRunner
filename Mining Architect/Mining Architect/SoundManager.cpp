#include "SoundManager.h"

SoundManager* SoundManager::me;

SoundManager* SoundManager::getManager()
{
	
	if(!me)
	{
		Mix_AllocateChannels(99999);
		me=new SoundManager();
	}
	return me;
}

SoundManager::SoundManager(void)
{
	sound = true;
}


SoundManager::~SoundManager(void)
{
}


/*
--------------------
Load the required Sound files
--------------------
*/
bool SoundManager::loadSound(){
	 //Loading success flag
    bool success = true;

	if(sound)
	{
		 //Load music
		backgroundMusic = Mix_LoadMUS( "images/bgMusic.ogg" );
		if( backgroundMusic == nullptr )
		{
			printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
			success = false;
			sound=false;
		}
	}

	

	return success;
}
/*
--------------------
Starts a sound effect playing on first free channel
--------------------
*/
void SoundManager::startSound(Mix_Chunk* soundEffect)
{
	if(sound)
	{
		Mix_PlayChannel( -1, soundEffect, 0 );
	}
}

/*
--------------------
Starts playing music 
--------------------
*/
void SoundManager::startMusic(Mix_Music* music)
{
	  //If there is no music playing
	if(sound)
	{
		//Play the music
		Mix_PlayMusic( music, -1 );
	}
}

/*
--------------------
Stops playing music 
--------------------
*/
void SoundManager::stopMusic()
{
	if(sound)
	{
		//Stop the music
		 Mix_HaltMusic();
	}
}

/*
--------------------
Pauses if music is playing, if music is paused it resumes it
--------------------
*/
void SoundManager::pauseResumeMusic()
{
	//If the music is paused
	if(sound)
	{
		if( Mix_PausedMusic() == 1 )
		{
			//Resume the music
			Mix_ResumeMusic();
		}
		//If the music is playing
		else
		{
			//Pause the music
			Mix_PauseMusic();
		}
	}
}