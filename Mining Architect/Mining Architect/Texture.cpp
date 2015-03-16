#include "Texture.h"


Texture::Texture( SDL_Renderer* renderer,std::string path)
{
	loadTexture( renderer,path);
	hasSAT=false;
	SATpoints = vector<Vector2f>(0);
}
Texture::Texture( SDL_Renderer* renderer,std::string path,std::string textPath)
{
	loadTexture( renderer,path);
	hasSAT=true;
	SATpoints = vector<Vector2f>(0);
	loadSAT(textPath);
}

Texture::~Texture(void)
{
}

void Texture::loadTexture( SDL_Renderer* renderer,std::string path)
{
	//The final texture 
	texture = nullptr; 
	//Load image at specified path 
	surface = IMG_Load( path.c_str() ); 
	if( !surface ) 
	{ 
		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	} 
	else 
	{ 
		//Create blank streamable texture 
		pixels = (Uint32 *)surface->pixels;
		pixels[ ( 10 * surface->w ) + 10 ];
		texture = SDL_CreateTextureFromSurface(renderer,surface); 
		size = Vector2f(surface->w,surface->h);
	} 
}

void Texture::loadSAT(std::string path)
{
	string x;
	string y;
	ifstream file(path);
	if(file.is_open())
	{
		while(getline(file,x,','))
		{
			getline(file,y);
			SATpoints.push_back(Vector2f(atoi(x.c_str()),atoi(y.c_str())));
		}
	}
	else
	{
		hasSAT=false;
	}
}

Uint32* Texture::getPixels()
{
	return (Uint32 *)surface->pixels;
}

Uint32 Texture::get_pixel32(int x, int y )
{ 
	//Convert the pixels to 32 bit 
	Uint32 *pixels = (Uint32 *)surface->pixels;
	//Get the requested pixel 
	return pixels[ ( y * surface->w ) + x ]; 
}