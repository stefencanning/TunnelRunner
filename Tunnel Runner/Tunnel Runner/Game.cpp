#include "Game.h"


Game::Game(void)
{
	textureNum = 0;
	textureTime = 0;
	setScore = false;
	SoundManager::getManager()->startMusic(SoundManager::getManager()->backgroundMusic);

	TCHAR szPath[MAX_PATH];
	// Get path for each computer, non-user specific and non-roaming data.
	if ( SUCCEEDED( SHGetFolderPath( NULL, CSIDL_LOCAL_APPDATA, NULL, 0, szPath ) ) )
	{
		// Append product-specific path
		PathAppend( szPath, _T("\\Wolfbrand Games\\scores.txt") );
	}
	TCHAR szPath2[MAX_PATH];
	// Get path for each computer, non-user specific and non-roaming data.
	if ( SUCCEEDED( SHGetFolderPath( NULL, CSIDL_LOCAL_APPDATA, NULL, 0, szPath2 ) ) )
	{
		// Append product-specific path
		PathAppend( szPath2, _T("\\Wolfbrand Games\\distances.txt") );
	}
	ifstream file3(szPath);
	ifstream file4(szPath2);
	string line;
	if(file3.is_open())
	{
		for(int i=0; i <10; i++)
		{
			getline(file3,line);
			scores[i].first = line.substr(0,line.find(',')).c_str();
			scores[i].second = atoi(line.substr(line.find(',')+1).c_str());
			getline(file4,line);
			distances[i].first = line.substr(0,line.find(',')).c_str();
			distances[i].second = atoi(line.substr(line.find(',')+1).c_str());
		}
	}
	file3.close();
	file4.close();

}


Game::~Game(void)
{
	delete curText;

	TCHAR szPath[MAX_PATH];
	// Get path for each computer, non-user specific and non-roaming data.
	if ( SUCCEEDED( SHGetFolderPath( NULL, CSIDL_LOCAL_APPDATA, NULL, 0, szPath ) ) )
	{
		// Append product-specific path
		PathAppend( szPath, _T("\\Wolfbrand Games\\scores.txt") );
	}
	TCHAR szPath2[MAX_PATH];
	// Get path for each computer, non-user specific and non-roaming data.
	if ( SUCCEEDED( SHGetFolderPath( NULL, CSIDL_LOCAL_APPDATA, NULL, 0, szPath2 ) ) )
	{
		// Append product-specific path
		PathAppend( szPath2, _T("\\Wolfbrand Games\\distances.txt") );
	}

	ofstream file(szPath);
	ofstream file2(szPath2);
	if(file.is_open())
	{
		for(int i = 0; i < 10; i++)
		{
			file << scores[i].first << ',' << scores[i].second << '\n';
			file2 << distances[i].first << ',' << distances[i].second << '\n';
		}
	}
	file.close();
	file2.close();
}

void Game::update(float timeElapsed)
{
	if(ObjectManager::getManager()->health > 0)
	{
		ObjectManager::getManager()->update(timeElapsed);
	}
	else
	{
		if(!setScore)
		{
			name = "";
			distPos =- 1;
			scorePos =- 1;
			setScore = true;
			updateScore();
		}
		for(int i = 4; i < 30; i++)
		{
			if(KeyManager::getManager()->keyPressed((SDL_Scancode)i))
			{
				if(name.size() < 12)
				{
					name += (char)(i + 93);
				}
			}
		}
		if(KeyManager::getManager()->keyPressed(SDL_SCANCODE_BACKSPACE))
		{
			if(name.size() > 0)
			{
				name.erase(name.end() - 1);
			}
		}
		if(scorePos != -1)
		{
			scores[scorePos].first = name;
		}
		if(distPos != -1)
		{
			distances[distPos].first = name;
		}
		if(KeyManager::getManager()->keyPressed(SDL_SCANCODE_RETURN))
		{
			ObjectManager::getManager()->setUp();
			setScore = false;
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
		pos.w = TextureManager::getManager()->scoreScreen->getSize().x;
		pos.h = TextureManager::getManager()->scoreScreen->getSize().y;
		pos.x = 640 - (pos.w / 2);
		pos.y = 360 - (pos.h / 2);
		SDL_RenderCopyEx(renderer, TextureManager::getManager()->scoreScreen->getTexture(), nullptr, &pos, 0, nullptr, SDL_RendererFlip::SDL_FLIP_NONE);


		TextureManager::getManager()->drawText(renderer, "Score", 640 - (960 / 2) + (450 / 2), 360 - (540 / 2) + 60 - (48),TextureManager::positioning::center);		
		TextureManager::getManager()->drawText(renderer,"Distance",640 + (960 / 2) - (450 / 2), 360 - (540 / 2) + 60 - (48),TextureManager::positioning::center);

		for(int i = 0; i < 10; i++)
		{
			int w = 0;
			int h = 0;
			if(scores[i].first != "")
			{
				TextureManager::getManager()->drawText(renderer, scores[i].first, 640 - (960 / 2) + (450 / 2) - (450 / 4), 360 - (540 / 2) + 60 + (i * 48), TextureManager::positioning::center);
			}
			
			TextureManager::getManager()->drawText(renderer,std::to_string((int)scores[i].second), 640 - (960 / 2) + (450 / 2) + (450 / 4), 360 - (540 / 2) + 60 + (i * 48),TextureManager::positioning::center);
			
			if(distances[i].first != "")
			{
				TextureManager::getManager()->drawText(renderer, distances[i].first, 640 + (960 / 2) - (450 / 2) - (450 / 4), 360 - (540 / 2) + 60 + (i * 48), TextureManager::positioning::center);
			}			
			TextureManager::getManager()->drawText(renderer, std::to_string((int)distances[i].second), 640 + (960 / 2) - (450 / 2) - (450 / 4), 360 - (540 / 2) + 60 + (i * 48), TextureManager::positioning::center);
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
			scorePos = i;
			for(int k = 9; k > i; k--)
			{
				scores[k].second = scores[k - 1].second;
				scores[k].first = scores[k - 1].first;
			}
			scores[i].second = ObjectManager::getManager()->score;
			break;
		}
	}
	for(int i = 0; i < 10; i++)
	{
		if(distances[i].second < ObjectManager::getManager()->playerPos.y)
		{
			distPos = i;
			for(int k = 9; k >= i; k--)
			{
				distances[k].second = distances[k-1].second;
				distances[k].first = distances[k-1].first;
			}
			distances[i].second = ObjectManager::getManager()->playerPos.y;
			break;
		}
	}
}