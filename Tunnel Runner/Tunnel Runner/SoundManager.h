#pragma once
#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H
#include "SDL_ttf.h"
#include <SDL_mixer.h>
#include <stdio.h>

///This is where all sounds are player through
class SoundManager
{
private:
	static SoundManager* me;///self
public:
	bool sound;
	SoundManager(void);
	~SoundManager(void);
	bool loadSound();
	///for sound effects
	void startSound(Mix_Chunk* soundEffect);///Starts playing the passed sounds

	///for music
	void startMusic(Mix_Music* music);///used to  start sounds that will loop
	void stopMusic();///stops something that was set to loop
	void pauseResumeMusic();///called to pause/ resume the currently playing music

	static SoundManager* getManager();///get self

	
	

	//music
	Mix_Music* backgroundMusic;///the background music for gameplay



	

};
#endif

