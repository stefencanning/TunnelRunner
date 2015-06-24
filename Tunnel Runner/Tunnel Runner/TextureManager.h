#pragma once
#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H
#include "SDL_ttf.h"
#include "Texture.h"
#include <vector>
#include "Constants.h"
using namespace std;
class TextureManager
{
private:
	static TextureManager* me;
public:
	enum positioning
	{
		left,
		center,
		right
	};
	void drawText(SDL_Renderer* renderer,string text,int x,int y,positioning position);


	TextureManager(void);
	~TextureManager(void);
	void loadTexture();
	static TextureManager* getManager();
	void createArrays();

	
	//backgrounds
	Texture *player;
	Texture *wall;
	Texture *magma; 
	Texture *lava; 
	Texture *gold; 
	Texture *bedrock; 
	Texture *scoreScreen; 
	Texture *water; 
	vector<Texture*>* miners;

	//font
	TTF_Font *font;
	TTF_Font *fontInner;
	TTF_Font *fontText;

};
#endif

