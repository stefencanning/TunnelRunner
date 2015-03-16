#include "Game.h"


Game::Game(void)
{
	textureNum = 0;
	textureTime=0;
	setScore=false;
	
	SoundManager::getManager()->startMusic(SoundManager::getManager()->backgroundMusic);
	ifstream file("images/scores.txt");
	ifstream file2("images/distances.txt");
	string line;
	//Crew::nameOptions[150];
	if(file.is_open())
	{
		for(int i=0; i <10; i++)
		{
			getline(file,line);
			scores[i].first = line.substr(0,line.find(',')).c_str();
			scores[i].second = atoi(line.substr(line.find(',')+1).c_str());
			getline(file2,line);
			distances[i].first = line.substr(0,line.find(',')).c_str();
			distances[i].second = atoi(line.substr(line.find(',')+1).c_str());
		}
	}
}


Game::~Game(void)
{
	delete curText;
	ofstream file("images/scores.txt");
	ofstream file2("images/distances.txt");
	if(file.is_open())
	{
		for(int i=0; i <10; i++)
		{
			file<<scores[i].first<<','<<scores[i].second<<'\n';
			file2<<distances[i].first<<','<<distances[i].second<<'\n';
		}
	}
}

void Game::update(float timeElapsed)
{
	if(ObjectManager::getManager()->health>0)
	{
		ObjectManager::getManager()->update(timeElapsed);
	}
	else
	{
		if(!setScore)
		{
			name="";
			distPos=-1;
			scorePos=-1;
			setScore=true;
			updateScore();
		}
		for(int i =4; i <30;i++)
		{
			if(KeyManager::getManager()->keyPressed((SDL_Scancode)i))
			{
				if(name.size()<12)
				{
					name+=(char)(i+93);
				}
			}
		}
		if(KeyManager::getManager()->keyPressed(SDL_SCANCODE_BACKSPACE))
		{
			if(name.size()>0)
			{
				name.erase(name.end()-1);
			}
		}
		if(scorePos!=-1)
		{
			scores[scorePos].first=name;
		}
		if(distPos!=-1)
		{
			distances[distPos].first=name;
		}
		if(KeyManager::getManager()->keyPressed(SDL_SCANCODE_RETURN))
		{
			ObjectManager::getManager()->setUp();
			setScore=false;
			SoundManager::getManager()->startMusic(SoundManager::getManager()->backgroundMusic);
		}
	}
	ObjectManager::getManager()->LavaUpdate(timeElapsed);
}

void Game::draw(SDL_Renderer* renderer)
{
	SDL_RenderClear(renderer);
	ObjectManager::getManager()->draw( renderer);
	if(ObjectManager::getManager()->health<=0)
	{	
		SDL_Rect pos;
		pos.w=TextureManager::getManager()->scoreScreen->getSize().x;
		pos.h=TextureManager::getManager()->scoreScreen->getSize().y;
		pos.x = 640-(pos.w/2);
		pos.y = 360-(pos.h/2);
		SDL_RenderCopyEx(renderer,TextureManager::getManager()->scoreScreen->getTexture(),nullptr,&pos,0,nullptr,SDL_RendererFlip::SDL_FLIP_NONE);

		
		SDL_Color fontColor;
		fontColor.r = 253;
		fontColor.g = 217;
		fontColor.b = 0;
		fontColor.a = 255;
		int w = 0;
		int h = 0;
		std::string scoreStr ="score";
		SDL_Surface* message = TTF_RenderText_Solid(TextureManager::getManager()->font,scoreStr.c_str(), fontColor);
		SDL_Texture* text = SDL_CreateTextureFromSurface(renderer, message);
		SDL_QueryTexture(text, nullptr, nullptr, &w, &h);
		int width = message->w;
		int height = message->h;
		
		pos.x = 640-(960/2)+(450/2);
		pos.y = 360-(540/2)+80-(48);
		pos.w = message->w;
		pos.h = message->h;
		pos.x -= message->w/2;
		pos.y -= message->h/2;
		SDL_RenderCopyEx(renderer, text, nullptr, &pos, 0, nullptr, SDL_FLIP_NONE);
		SDL_FreeSurface(message);
		SDL_DestroyTexture(text);


		std::string distStr ="distance";
		message = TTF_RenderText_Solid(TextureManager::getManager()->font,distStr.c_str(), fontColor);
		text = SDL_CreateTextureFromSurface(renderer, message);
		SDL_QueryTexture(text, nullptr, nullptr, &w, &h);
		width = message->w;
		height = message->h;

		pos.x = 640+(960/2)-(450/2);
		pos.y = 360-(540/2)+80-(48);
		pos.w = message->w;
		pos.h = message->h;
		pos.x -= message->w/2;
		pos.y -= message->h/2;
		SDL_RenderCopyEx(renderer, text, nullptr, &pos, 0, nullptr, SDL_FLIP_NONE);
		SDL_FreeSurface(message);
		SDL_DestroyTexture(text);

		for(int i = 0; i < 10; i++)
		{
			int w = 0;
			int h = 0;

			if(i!=scorePos)
			{
				fontColor.r = 253;
				fontColor.g = 217;
				fontColor.b = 0;
				fontColor.a = 255;
			}
			else
			{
				fontColor.r = 255;
				fontColor.g = 255;
				fontColor.b = 255;
				fontColor.a = 255;
			}

			if(scores[i].first!="")
			{
				scoreStr=scores[i].first;
				SDL_Surface* message = TTF_RenderText_Solid(TextureManager::getManager()->font,scoreStr.c_str(), fontColor);
				SDL_Texture* text = SDL_CreateTextureFromSurface(renderer, message);
				SDL_QueryTexture(text, nullptr, nullptr, &w, &h);
				int width = message->w;
				int height = message->h;

				pos.x = 640-(960/2)+(450/2)-(450/4);
				pos.y = 360-(540/2)+80+(i*48);
				pos.w = message->w;
				pos.h = message->h;
				pos.x -= message->w/2;
				pos.y -= message->h/2;
				SDL_RenderCopyEx(renderer, text, nullptr, &pos, 0, nullptr, SDL_FLIP_NONE);
				SDL_FreeSurface(message);
				SDL_DestroyTexture(text);
			}





			scoreStr =std::to_string((int)scores[i].second);
			message = TTF_RenderText_Solid(TextureManager::getManager()->font,scoreStr.c_str(), fontColor);
			text = SDL_CreateTextureFromSurface(renderer, message);
			SDL_QueryTexture(text, nullptr, nullptr, &w, &h);
			width = message->w;
			height = message->h;

			pos.x = 640-(960/2)+(450/2)+(450/4);
			pos.y = 360-(540/2)+80+(i*48);
			pos.w = message->w;
			pos.h = message->h;
			pos.x -= message->w/2;
			pos.y -= message->h/2;
			SDL_RenderCopyEx(renderer, text, nullptr, &pos, 0, nullptr, SDL_FLIP_NONE);
			SDL_FreeSurface(message);
			SDL_DestroyTexture(text);
			

			if(i!=distPos)
			{
				fontColor.r = 253;
				fontColor.g = 217;
				fontColor.b = 0;
				fontColor.a = 255;
			}
			else
			{
				fontColor.r = 255;
				fontColor.g = 255;
				fontColor.b = 255;
				fontColor.a = 255;
			}
			if(distances[i].first!="")
			{
				scoreStr =distances[i].first;
				message = TTF_RenderText_Solid(TextureManager::getManager()->font,scoreStr.c_str(), fontColor);
				text = SDL_CreateTextureFromSurface(renderer, message);
				SDL_QueryTexture(text, nullptr, nullptr, &w, &h);
				width = message->w;
				height = message->h;
			
				pos.x = 640+(960/2)-(450/2)-(450/4);
				pos.y = 360-(540/2)+80+(i*48);
				pos.w = message->w;
				pos.h = message->h;
				pos.x -= message->w/2;
				pos.y -= message->h/2;
				SDL_RenderCopyEx(renderer, text, nullptr, &pos, 0, nullptr, SDL_FLIP_NONE);
				SDL_FreeSurface(message);
				SDL_DestroyTexture(text);
			}



			distStr =std::to_string((int)distances[i].second);
			message = TTF_RenderText_Solid(TextureManager::getManager()->font,distStr.c_str(), fontColor);
			text = SDL_CreateTextureFromSurface(renderer, message);
			SDL_QueryTexture(text, nullptr, nullptr, &w, &h);
			width = message->w;
			height = message->h;
			
			pos.x = 640+(960/2)-(450/2)+(450/4);
			pos.y = 360-(540/2)+80+(i*48);
			pos.w = message->w;
			pos.h = message->h;
			pos.x -= message->w/2;
			pos.y -= message->h/2;
			SDL_RenderCopyEx(renderer, text, nullptr, &pos, 0, nullptr, SDL_FLIP_NONE);
			SDL_FreeSurface(message);
			SDL_DestroyTexture(text);
		}
	}
	SDL_RenderPresent(renderer);
}

void Game::updateScore()
{
	for(int i = 0; i < 10; i++)
	{
		if(scores[i].second < ObjectManager::getManager()->score)
		{
			scorePos=i;
			for(int k = 9; k > i; k--)
			{
				scores[k].second = scores[k-1].second;
			}
			scores[i].second= ObjectManager::getManager()->score;
			break;
		}
	}
	for(int i = 0; i < 10; i++)
	{
		if(distances[i].second < ObjectManager::getManager()->playerPos.y)
		{
			distPos=i;
			for(int k = 9; k >= i; k--)
			{
				distances[k].second = distances[k-1].second;
			}
			distances[i].second= ObjectManager::getManager()->playerPos.y;
			break;
		}
	}
}