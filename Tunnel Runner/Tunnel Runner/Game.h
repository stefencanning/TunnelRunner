#pragma once
#ifndef GAME_H
#define GAME_H
#include "ObjectManager.h"
#include "SoundManager.h"
#include "TextureManager.h"
#include <time.h>
#include <sstream>
#include "Shlobj.h"
#include <shlwapi.h>
#pragma comment(lib,"shlwapi.lib")
#include <tchar.h>
using namespace std;

class Game
{
private:
public:
	Game(void); /// constructor for game
	~Game(void); /// destructor for game 
	void update(float timeElapsed); /// update method for game which has time elapsed as an arguement
	void draw(SDL_Renderer* renderer); /// the draw method which uses the SDL renderer
	Texture* curText; /// the current background texture
	int textureNum; /// the current texture number
	float textureTime; /// the time the texture has been on screen
	pair<string,float> scores[10];
	pair<string,float> distances[10];
	void updateScore();
	bool setScore;
	int scorePos;
	int distPos;
	string name;
};
#endif