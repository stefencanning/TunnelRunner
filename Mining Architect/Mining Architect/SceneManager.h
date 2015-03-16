#pragma once
#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H
#include "Game.h"

///Controls whether the game of menu is active
class SceneManager
{
private:
	static SceneManager* me;//contains the scenemanager
public:
	SceneManager(void);
	~SceneManager(void);
	static SceneManager* getManager();///return self
	void update(float timeElapsed);///Run the current scene - game/menu
	void draw(SDL_Renderer* renderer);///Draw the current scene - game/menu
	Game* game;
};
#endif

