#include "ObjectManager.h"

ObjectManager* ObjectManager::me;

ObjectManager* ObjectManager::getManager()
{
	if(!me)
	{
		me=new ObjectManager();
	}
	return me;
}

ObjectManager::ObjectManager(void):none(0),mud(1),magma(2),size(16),lava(3),flow(4),bedrock(5),gold(6),water(7),waterHeal(5)
{
	playerPos = Vector2f(640,0);
	accel=0;
	score=0;
	health=100;
	spawnChance = 600;
	lineDel=0;
	textureChange=0.0f;
	playerTex=0;
	texNum=0;
	flip=false;
	map = vector<vector<short>>();
	for(int k = 0; k < 1440/size;k++)
	{
		vector<short> line = vector<short>();
		for(int i = 0; i < 1280/size;i++)
		{
			if((k==0&&(i==0||i==(1280/size)-1)))
			{
				line.push_back(magma);
			}
			else if(k<5)
			{
				if(i<k)
				{
					line.push_back(mud);
				}
				else if(abs(i-(1280/size))<=k)
				{
					line.push_back(mud);
				}
				else
				{
					line.push_back(none);
				}
			}
			else
			{
				int num = rand()%(int)spawnChance;
				if(num<=spawnChance-25)
				{
					line.push_back(mud);
				}
				else if(num <=spawnChance-9)
				{
					line.push_back(gold);
				}
				else if(num <=spawnChance-5)
				{
					line.push_back(bedrock);
				}
				else if(num <=spawnChance-3)
				{
					line.push_back(lava);
				}
				else if(num <=spawnChance-1)
				{
					line.push_back(water);
				}
			}
		}
		spawnChance = max(spawnChance-2.0f,300.0f);
		map.push_back(line);
	}
	timeTillMove=0;
	timeTillMoveCounter=2;
}

ObjectManager::~ObjectManager(void)
{

}

void ObjectManager::update(float timeElapsed)
{
	playerPos.y+=min(max(accel*timeElapsed,-10.0f),10.0f);
	bool struck = false;
	if(KeyManager::getManager()->keyDown(SDL_SCANCODE_A)||KeyManager::getManager()->keyDown(SDL_SCANCODE_LEFT))
	{
		flip=true;
		playerPos.x=max(0.0f,playerPos.x-min(120*timeElapsed/max(timeTillMoveCounter,0.5f),15.0f));
		for(int i = max(0,(int)((playerPos.y-32)/size)-lineDel); i <min((int)map.size(),(int)((playerPos.y+64)/size)-lineDel);i++)
		{
			for(int k = max(0,(int)((playerPos.x-32)/size)); k <min((int)map.at(i).size(),(int)((playerPos.x+64)/size));k++)
			{
				if(map.at(i).at(k)==mud)
				{
					if(playerPos.x+32>(k)*size&&playerPos.x<(k+1)*size&&playerPos.y+32-(size/4)>(i+lineDel)*size&&playerPos.y+(size/4)<(i+1+lineDel)*size)
					{
						map.at(i).at(k)=none;
					}
				}
				else if(map.at(i).at(k)==gold)
				{
					if(playerPos.x+32>(k)*size&&playerPos.x<(k+1)*size&&playerPos.y+32-(size/4)>(i+lineDel)*size&&playerPos.y+(size/4)<(i+1+lineDel)*size)
					{
						map.at(i).at(k)=none;
						score+=10;
					}
				}
				else if(map.at(i).at(k)==water)
				{
					if(playerPos.x+32>(k)*size&&playerPos.x<(k+1)*size&&playerPos.y+32-(size/4)>(i+lineDel)*size&&playerPos.y+(size/4)<(i+1+lineDel)*size)
					{
						map.at(i).at(k)=none;
						health+=waterHeal;
					}
				}
				else if(map.at(i).at(k)==bedrock)
				{
					if(playerPos.x+32>(k)*size&&playerPos.x<(k+1)*size&&playerPos.y+32-(size/4)>(i+lineDel)*size&&playerPos.y+(size/4)<(i+1+lineDel)*size)
					{
						playerPos.x=(k+1)*size;
						struck=true;
					}
				}
			}
		}
	}
	if(KeyManager::getManager()->keyDown(SDL_SCANCODE_D)||KeyManager::getManager()->keyDown(SDL_SCANCODE_RIGHT))
	{
		flip=false;
		playerPos.x=min(1280-32.0f,playerPos.x+min(120*timeElapsed/max(timeTillMoveCounter,0.5f),15.0f));
		for(int i = max(0,(int)((playerPos.y-32)/size)-lineDel); i <min((int)map.size(),(int)((playerPos.y+64)/size)-lineDel);i++)
		{
			for(int k = max(0,(int)((playerPos.x-32)/size)); k <min((int)map.at(i).size(),(int)((playerPos.x+64)/size));k++)
			{
				if(map.at(i).at(k)==mud)
				{
					if(playerPos.x+32>(k)*size&&playerPos.x<(k+1)*size&&playerPos.y+32-(size/4)>(i+lineDel)*size&&playerPos.y+(size/4)<(i+1+lineDel)*size)
					{
						map.at(i).at(k)=none;
					}
				}
				else if(map.at(i).at(k)==gold)
				{
					if(playerPos.x+32>(k)*size&&playerPos.x<(k+1)*size&&playerPos.y+32-(size/4)>(i+lineDel)*size&&playerPos.y+(size/4)<(i+1+lineDel)*size)
					{
						map.at(i).at(k)=none;
						score+=10;
					}
				}
				else if(map.at(i).at(k)==water)
				{
					if(playerPos.x+32>(k)*size&&playerPos.x<(k+1)*size&&playerPos.y+32-(size/4)>(i+lineDel)*size&&playerPos.y+(size/4)<(i+1+lineDel)*size)
					{
						map.at(i).at(k)=none;
						health+=waterHeal;
					}
				}
				else if(map.at(i).at(k)==bedrock)
				{
					if(playerPos.x+32>(k)*size&&playerPos.x<(k+1)*size&&playerPos.y+32-(size/4)>(i+lineDel)*size&&playerPos.y+(size/4)<(i+1+lineDel)*size)
					{
						playerPos.x = (k*size)-32;
						struck=true;
					}
				}
			}
		}
	}
	if(KeyManager::getManager()->keyDown(SDL_SCANCODE_S)||KeyManager::getManager()->keyDown(SDL_SCANCODE_DOWN))
	{
		for(int i = max(0,(int)((playerPos.y+32)/size)-lineDel); i <min((int)map.size(),(int)((playerPos.y+64)/size)-lineDel);i++)
		{
			for(int k = max(0,(int)((playerPos.x-32)/size)); k <min((int)map.at(i).size(),(int)((playerPos.x+64)/size));k++)
			{
				if(map.at(i).at(k)==mud)
				{
					if(playerPos.x+32>(k)*size&&playerPos.x<(k+1)*size&&playerPos.y+32+(size/2)>(i)*size&&playerPos.y<(i+1+lineDel)*size)
					{
						map.at(i).at(k)=none;
					}
				}
				if(map.at(i).at(k)==gold)
				{
					if(playerPos.x+32>(k)*size&&playerPos.x<(k+1)*size&&playerPos.y+32+(size/2)>(i+lineDel)*size&&playerPos.y<(i+1+lineDel)*size)
					{
						map.at(i).at(k)=none;
						score+=10;
					}
				}
				if(map.at(i).at(k)==water)
				{
					if(playerPos.x+32>(k)*size&&playerPos.x<(k+1)*size&&playerPos.y+32+(size/2)>(i+lineDel)*size&&playerPos.y<(i+1+lineDel)*size)
					{
						map.at(i).at(k)=none;
						health+=waterHeal;
					}
				}
			}
		}
	}
	for(int i = max(0,(int)((playerPos.y-32)/size)-lineDel); i <min((int)map.size(),(int)((playerPos.y+64)/size)-lineDel);i++)
	{
		for(int k = max(0,(int)((playerPos.x-32)/size)); k <min((int)map.at(i).size(),(int)((playerPos.x+64)/size));k++)
		{
			if(map.at(i).at(k)==mud)
			{
				if(playerPos.x+32>(k)*size&&playerPos.x<(k+1)*size&&playerPos.y+32>(i+lineDel)*size&&playerPos.y<(i+1+lineDel)*size)
				{
					if(playerPos.y+(size/2)>((i+lineDel)*size))
					{
						map.at(i).at(k)=none;
					}
					else
					{
						playerPos.y = (i+lineDel)*size-32;
						struck=true;
						accel=0;
					}
				}
			}
			else if(map.at(i).at(k)==gold)
			{
				if(playerPos.x+32>(k)*size&&playerPos.x<(k+1)*size&&playerPos.y+32>(i+lineDel)*size&&playerPos.y<(i+1+lineDel)*size)
				{
					if(playerPos.y+(size/2)>((i+lineDel)*size))
					{
						map.at(i).at(k)=none;
						score+=10;
					}
					else
					{
						playerPos.y = (i+lineDel)*size-32;
						struck=true;
						accel=0;
					}
				}
			}
			else if(map.at(i).at(k)==water)
			{
				if(playerPos.x+32>(k)*size&&playerPos.x<(k+1)*size&&playerPos.y+32>(i+lineDel)*size&&playerPos.y<(i+1+lineDel)*size)
				{
					if(playerPos.y+(size/2)>((i+lineDel)*size))
					{
						map.at(i).at(k)=none;
						health+=waterHeal;
					}
					else
					{
						playerPos.y = (i+lineDel)*size-32;
						struck=true;
						accel=0;
					}
				}
			}
			else if(map.at(i).at(k)==bedrock)
			{
				if(playerPos.x+32>(k)*size&&playerPos.x<(k+1)*size&&playerPos.y+32>(i+lineDel)*size&&playerPos.y<(i+1+lineDel)*size)
				{
					if(playerPos.y+(size/2)>((i+lineDel)*size))
					{
						playerPos.y = (i+1+lineDel)*size;
						accel=0;
						struck=true;
					}
					else
					{
						playerPos.y = (i+lineDel)*size-32;
						accel=0;
						struck=true;
					}
				}
			}
			else if(map.at(i).at(k)==lava)
			{
				if(playerPos.x+32>(k)*size&&playerPos.x<(k+1)*size&&playerPos.y+32>(i+lineDel)*size&&playerPos.y<(i+1+lineDel)*size)
				{
					health-=10*timeElapsed;
				}
			}
		}
	}
	if(KeyManager::getManager()->keyPressed(SDL_SCANCODE_W)||KeyManager::getManager()->keyDown(SDL_SCANCODE_UP))
	{
		if(accel==0)
		{
			accel=-100/max(timeTillMoveCounter,0.5f);
		}
	}
	if(health>100)
	{
		health=100;
	}
	if(playerPos.y+400>(map.size()+lineDel)*size)
	{
		vector<short> line=vector<short>();
		for(int i = 0; i < 1280/size; i++)
		{
			int num = rand()%(int)spawnChance;
			if(num<=spawnChance-25)
			{
				line.push_back(mud);
			}
			else if(num <=spawnChance-9)
			{
				line.push_back(gold);
			}
			else if(num <=spawnChance-5)
			{
				line.push_back(bedrock);
			}
			else if(num <=spawnChance-3)
			{
				line.push_back(lava);
			}
			else if(num <=spawnChance-1)
			{
				line.push_back(water);
			}
		}
		spawnChance = max(spawnChance-2.0f,300.0f);
		map.push_back(line);
	}
	if(map.size()>2000/size)
	{
		map.erase(map.begin()+1);
		lineDel+=1;
	}
	accel+=98*timeElapsed/max(timeTillMoveCounter,0.5f);
	if(KeyManager::getManager()->keyDown(SDL_SCANCODE_A)||KeyManager::getManager()->keyDown(SDL_SCANCODE_D)||
		KeyManager::getManager()->keyDown(SDL_SCANCODE_W)||KeyManager::getManager()->keyDown(SDL_SCANCODE_S)||
		KeyManager::getManager()->keyDown(SDL_SCANCODE_LEFT)||KeyManager::getManager()->keyDown(SDL_SCANCODE_RIGHT)||
		KeyManager::getManager()->keyDown(SDL_SCANCODE_UP)||KeyManager::getManager()->keyDown(SDL_SCANCODE_DOWN))
	{
		textureChange-=timeElapsed*5;
		if(textureChange<=0)
		{
			playerTex = (playerTex+1)%2;
			textureChange=max(timeTillMoveCounter,0.3f);
		}
		if(KeyManager::getManager()->keyDown(SDL_SCANCODE_S)||KeyManager::getManager()->keyDown(SDL_SCANCODE_DOWN))
		{
			texNum=falling;
			if(KeyManager::getManager()->keyDown(SDL_SCANCODE_A)||KeyManager::getManager()->keyDown(SDL_SCANCODE_D)||
				KeyManager::getManager()->keyDown(SDL_SCANCODE_LEFT)||KeyManager::getManager()->keyDown(SDL_SCANCODE_RIGHT))
			{
				texNum=floating;
			}

		}
		else if(KeyManager::getManager()->keyDown(SDL_SCANCODE_W)||KeyManager::getManager()->keyDown(SDL_SCANCODE_UP))
		{
			texNum=upSide;
		}
		else if(KeyManager::getManager()->keyDown(SDL_SCANCODE_A)||KeyManager::getManager()->keyDown(SDL_SCANCODE_D)||
			KeyManager::getManager()->keyDown(SDL_SCANCODE_LEFT)||KeyManager::getManager()->keyDown(SDL_SCANCODE_RIGHT))
		{
			texNum=side;
		}
	}
	
	if(struck)
	{
		if(texNum==falling)
		{
			texNum=down;
		}
		if(texNum==floating)
		{
			texNum=downSide;
		}
	}





}


void ObjectManager::LavaUpdate(float timeElapsed)
{
	timeTillMove-=timeElapsed;
	if(timeTillMove<=0)
	{
		timeTillMove=timeTillMoveCounter;
		timeTillMoveCounter=max(timeTillMoveCounter-0.25,0.1);
		for(int i = 0; i < map.size(); i++)
		{
			for(int k = 0; k < map.at(k).size();k++)
			{
				if(map.at(i).at(k)==lava)
				{
					int left= max(0,k-1);
					int right=min( (int)map.at(i).size()-1,k+1);
					int up = max(0,i-1);
					int down = min( (int)map.size()-1,i+1);
					if(map.at(up).at(k)==none)
					{
						map.at(up).at(k)=magma;
					}
					if(map.at(down).at(k)==none)
					{
						map.at(down).at(k)=flow;
					}
					if(map.at(i).at(left)==none)
					{
						if(map.at(down).at(left)==lava||map.at(down).at(left)==magma||map.at(down).at(left)==mud||map.at(down).at(left)==gold||map.at(down).at(left)==bedrock||map.at(down).at(k)==mud||map.at(down).at(k)==gold||map.at(down).at(k)==bedrock)
						{
							map.at(i).at(left)=lava;
						}
					}
					if(map.at(i).at(right)==none)
					{
						if(map.at(down).at(right)==lava||map.at(down).at(right)==magma||map.at(down).at(right)==mud||map.at(down).at(right)==gold||map.at(down).at(right)==bedrock||map.at(down).at(k)==mud||map.at(down).at(k)==gold||map.at(down).at(k)==bedrock)
						{
							map.at(i).at(right)=magma;
						}
					}
					if(map.at(up).at(k)==water)
					{
						map.at(up).at(k)=bedrock;
					}
					if(map.at(down).at(k)==water)
					{
						map.at(down).at(k)=bedrock;
					}
					if(map.at(i).at(left)==water)
					{
						map.at(i).at(left)=bedrock;
					}
					if(map.at(i).at(right)==water)
					{
						map.at(i).at(right)=bedrock;
					}
				}
				else 
				if(map.at(i).at(k)==flow)
				{
					map.at(i).at(k)=lava;
					int left= max(0,k-1);
					int right=min( (int)map.at(i).size()-1,k+1);
					int up = max(0,i-1);
					int down = min( (int)map.size()-1,i+1);
					if(map.at(up).at(k)==none)
					{
						map.at(up).at(k)=magma;
					}
					if(map.at(down).at(k)==none)
					{
						map.at(down).at(k)=magma;
					}
					if(map.at(i).at(left)==none)
					{
						if(map.at(down).at(left)==lava||map.at(down).at(left)==magma||map.at(down).at(left)==mud||map.at(down).at(left)==gold||map.at(down).at(left)==bedrock||map.at(down).at(k)==mud||map.at(down).at(k)==gold||map.at(down).at(k)==bedrock)
						{
							map.at(i).at(left)=lava;
						}
					}
					if(map.at(i).at(right)==none)
					{
						if(map.at(down).at(right)==lava||map.at(down).at(right)==magma||map.at(down).at(right)==mud||map.at(down).at(left)==gold||map.at(down).at(left)==bedrock||map.at(down).at(k)==mud||map.at(down).at(k)==gold||map.at(down).at(k)==bedrock)
						{
							map.at(i).at(right)=magma;
						}
					}
				}
				else if(map.at(i).at(k)==magma)
				{
					map.at(i).at(k)=lava;
				}
			}
		}
	}
}

void ObjectManager::draw(SDL_Renderer* renderer)
{
	SDL_Rect pos;
	pos.w=size;
	pos.h=size;
	for(int i = max(0,(int)((playerPos.y-400)/size)-lineDel); i < min((int)map.size(),(int)((playerPos.y+400)/size)-lineDel);i++)
	{
		pos.y = ((i+lineDel)*size)-playerPos.y+360;
		for(int k = 0; k < map.at(i).size(); k++)
		{
			if(map.at(i).at(k)==mud)
			{
				pos.x =(k)*size;
				SDL_RenderCopyEx(renderer,TextureManager::getManager()->wall->getTexture(),nullptr,&pos,0,nullptr,SDL_RendererFlip::SDL_FLIP_NONE);
			}
			else if(map.at(i).at(k)==magma)
			{
				pos.x =(k)*size;
				SDL_RenderCopyEx(renderer,TextureManager::getManager()->magma->getTexture(),nullptr,&pos,0,nullptr,SDL_RendererFlip::SDL_FLIP_NONE);
			}
			else if(map.at(i).at(k)==lava)
			{
				pos.x =(k)*size;
				SDL_RenderCopyEx(renderer,TextureManager::getManager()->lava->getTexture(),nullptr,&pos,0,nullptr,SDL_RendererFlip::SDL_FLIP_NONE);
			}
			else if(map.at(i).at(k)==gold)
			{
				pos.x =(k)*size;
				SDL_RenderCopyEx(renderer,TextureManager::getManager()->gold->getTexture(),nullptr,&pos,0,nullptr,SDL_RendererFlip::SDL_FLIP_NONE);
			}
			else if(map.at(i).at(k)==water)
			{
				pos.x =(k)*size;
				SDL_RenderCopyEx(renderer,TextureManager::getManager()->water->getTexture(),nullptr,&pos,0,nullptr,SDL_RendererFlip::SDL_FLIP_NONE);
			}
			else if(map.at(i).at(k)==bedrock)
			{
				pos.x =(k)*size;
				SDL_RenderCopyEx(renderer,TextureManager::getManager()->bedrock->getTexture(),nullptr,&pos,0,nullptr,SDL_RendererFlip::SDL_FLIP_NONE);
			}
		}
	}

	pos.x = playerPos.x;
	pos.y = playerPos.y-playerPos.y+360;
	pos.w = 32;
	pos.h = 32;
	SDL_RenderCopyEx(renderer,TextureManager::getManager()->miners->at(texNum+playerTex)->getTexture(),nullptr,&pos,0,nullptr,(SDL_RendererFlip)(int)flip);
		
	
	
	SDL_Rect posRec;
	SDL_Color black;
	black.r = 253;
	black.g = 217;
	black.b = 0;
	black.a = 255;
	int w = 0;
	int h = 0;
	
	TextureManager::getManager()->drawText(renderer,"Score: "+std::to_string(score),20,20,TextureManager::positioning::left);
	/*
	std::string scoreStr="Score: ";
	scoreStr+=std::to_string(score);
	SDL_Surface* message = TTF_RenderText_Solid(TextureManager::getManager()->font,scoreStr.c_str(), black);
	SDL_Texture* text = SDL_CreateTextureFromSurface(renderer, message);
	SDL_QueryTexture(text, nullptr, nullptr, &w, &h);
	int width = message->w;
	int height = message->h;

	posRec.x = 20;
	posRec.y = 20;
	posRec.w = message->w;
	posRec.h = message->h;
	SDL_RenderCopyEx(renderer, text, nullptr, &posRec, 0, nullptr, SDL_FLIP_NONE);
	SDL_FreeSurface(message);
	SDL_DestroyTexture(text);
	//*/

	TextureManager::getManager()->drawText(renderer,"Health: "+std::to_string((int)max(health,0.0f)), 1280-20,20,TextureManager::positioning::right);
	/*
	std::string healthStr="Health: ";
	healthStr+=std::to_string((int)max(health,0.0f));
	message = TTF_RenderText_Solid(TextureManager::getManager()->font,healthStr.c_str(), black);
	text = SDL_CreateTextureFromSurface(renderer, message);
	SDL_QueryTexture(text, nullptr, nullptr, &w, &h);
	width = message->w;
	height = message->h;

	posRec.x = 1280-20-width;
	posRec.y = 20;
	posRec.w = message->w;
	posRec.h = message->h;
	SDL_RenderCopyEx(renderer, text, nullptr, &posRec, 0, nullptr, SDL_FLIP_NONE);
	SDL_FreeSurface(message);
	SDL_DestroyTexture(text);
	*/
	
	TextureManager::getManager()->drawText(renderer,"Distance: "+std::to_string((int)playerPos.y), 640,20,TextureManager::positioning::center);
	/*
	std::string distanceStr="Distance: ";
	distanceStr+=std::to_string((int)playerPos.y);
	message = TTF_RenderText_Solid(TextureManager::getManager()->font,distanceStr.c_str(), black);
	text = SDL_CreateTextureFromSurface(renderer, message);
	SDL_QueryTexture(text, nullptr, nullptr, &w, &h);
	width = message->w;
	height = message->h;

	posRec.x = 640-(message->w/2);
	posRec.y = 20;
	posRec.w = message->w;
	posRec.h = message->h;
	SDL_RenderCopyEx(renderer, text, nullptr, &posRec, 0, nullptr, SDL_FLIP_NONE);
	SDL_FreeSurface(message);
	SDL_DestroyTexture(text);
	*/
}


void ObjectManager::setUp()
{
	playerPos = Vector2f(640,0);
	accel=0;
	score=0;
	health=100;
	spawnChance = 600;
	lineDel=0;
	map = vector<vector<short>>();
	for(int k = 0; k < 1440/size;k++)
	{
		vector<short> line = vector<short>();
		for(int i = 0; i < 1280/size;i++)
		{
			if((k==0&&(i==0||i==(1280/size)-1)))
			{
				line.push_back(magma);
			}
			else if(k<5)
			{
				if(i<k)
				{
					line.push_back(mud);
				}
				else if(abs(i-(1280/size))<=k)
				{
					line.push_back(mud);
				}
				else
				{
					line.push_back(none);
				}
			}
			else
			{
				int num = rand()%(int)spawnChance;
				if(num<=spawnChance-25)
				{
					line.push_back(mud);
				}
				else if(num <=spawnChance-9)
				{
					line.push_back(gold);
				}
				else if(num <=spawnChance-5)
				{
					line.push_back(bedrock);
				}
				else if(num <=spawnChance-3)
				{
					line.push_back(lava);
				}
				else if(num <=spawnChance-1)
				{
					line.push_back(water);
				}
			}
		}
		spawnChance = max(spawnChance-2.0f,300.0f);
		map.push_back(line);
	}
	timeTillMove=0;
	timeTillMoveCounter=2;
}