 #include "TextureManager.h"

TextureManager* TextureManager::me;

TextureManager* TextureManager::getManager()
{
	if(!me)
	{
		me=new TextureManager();
	}
	return me;
}


TextureManager::TextureManager(void)
{
}


TextureManager::~TextureManager(void)
{
}


void TextureManager::createArrays()
{
}



void TextureManager::drawText(SDL_Renderer* renderer,string textStr,int x,int y,positioning position)
{
	SDL_Rect pos;
	SDL_Color fontColor;
	fontColor.r = 0;
	fontColor.g = 0;
	fontColor.b = 0;
	fontColor.a = 255;
	int w = 0;
	int h = 0;
	SDL_Surface* message = TTF_RenderText_Solid(TextureManager::getManager()->font,textStr.c_str(), fontColor);
	SDL_Texture* text = SDL_CreateTextureFromSurface(renderer, message);
	SDL_QueryTexture(text, nullptr, nullptr, &w, &h);
	int width = message->w;
	int height = message->h;
	
	pos.x = x;
	pos.y = y;
	pos.w = message->w;
	pos.h = message->h;
	if(position==positioning::center)
	{
		pos.x -= message->w/2;
	}
	if(position==positioning::right)
	{
		pos.x -= message->w;
	}
	SDL_RenderCopyEx(renderer, text, nullptr, &pos, 0, nullptr, SDL_FLIP_NONE);
	SDL_FreeSurface(message);
	SDL_DestroyTexture(text);
	



	fontColor.r = 253;
	fontColor.g = 217;
	fontColor.b = 0;
	fontColor.a = 255;

	message = TTF_RenderText_Solid(TextureManager::getManager()->font,textStr.c_str(), fontColor);
	text = SDL_CreateTextureFromSurface(renderer, message);
	SDL_QueryTexture(text, nullptr, nullptr, &w, &h);
	width = message->w;
	height = message->h;
	
	pos.x += 1;
	pos.y += 1;
	SDL_RenderCopyEx(renderer, text, nullptr, &pos, 0, nullptr, SDL_FLIP_NONE);
	SDL_FreeSurface(message);
	SDL_DestroyTexture(text);
}