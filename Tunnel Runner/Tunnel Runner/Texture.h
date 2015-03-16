#pragma once
#include "SDL_ttf.h"
#include <SDL_image.h>
#include <string>
#include "Vector2f.h"
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;
class Texture
{
private:
	SDL_Texture *texture;
	SDL_Surface *surface; 
	Uint32 *pixels;
	Vector2f size;
	int pitch;
	bool hasSAT;
	vector<Vector2f> SATpoints;
public:
	static const int transparent = 16777215;
	Texture( SDL_Renderer* renderer,std::string path);
	Texture( SDL_Renderer* renderer,std::string path,std::string textPath);
	~Texture(void);
	SDL_Texture *getTexture(){return texture;};
	Uint32* getPixels(); 
	void loadTexture( SDL_Renderer* renderer,std::string path);
	void loadSAT(std::string path);
	Vector2f getSize(){return size;};
	Uint32 Texture::get_pixel32(int x, int y );
	SDL_Surface* getSurface(){return surface;};
	bool isSAT(){return hasSAT;};
	vector<Vector2f> getSAT(){return SATpoints;};
};

