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


ObjectManager::ObjectManager(void):none(0),mud(1),magma(2),size(16),lava(3),flow(4),bedrock(5),gold(6),water(7),waterHeal(5),
									m_playerOne(Vector2f(Constants::SCREEN_WIDTH / 2, 0)), accel(0), score(0), health(100), spawnChance(600), lineDel(0),
									textureChange(0.0f), playerTex(0), texNum(0), timeTillMove(0), timeTillMoveCounter(2),
									map(vector<vector<short>>())
{	

	/// For each line  twice the height of the screen, spawn a row of terrain
	for(int k = 0; k < Constants::SCREEN_HEIGHT * 2 / size; k++)
	{
		spawnTerrain();
	}
}


void ObjectManager::spawnTerrain()
{
	/// Check if a line is needed to be spawned at the current time
	if(m_playerOne.getPosition().y  + 400 > (map.size() + lineDel) * size)
	{
		/// Temporary vector storing blocks on the line
		vector<short> line = vector<short>();
		/// Iterate across the screen 
		for(int i = 0; i < Constants::SCREEN_WIDTH / size; i++)
		{
			/// If the current square is the first or last 2 lines horizontally, make it lava
			if((i <= 1 || i >= (Constants::SCREEN_WIDTH / size) - 2))
			{
				line.push_back(magma);				
			}
			/// Create ridges on the top of the map for lava to flow down
			else if(map.size() < 10)
			{
				if(i < map.size())
				{
					line.push_back(mud);
				}
				else if( abs(i - (Constants::SCREEN_WIDTH / size )) <= map.size())
				{
					line.push_back(mud);
				}
				else
				{
					line.push_back(none);
				}
			}
			/// Randomly spawn objects based on type and depth
			else
			{
				int num = rand() % (int)spawnChance;
				if(num <= spawnChance - 25)
				{
					line.push_back(mud);
				}
				else if(num <= spawnChance - 9)
				{
					line.push_back(gold);
				}
				else if(num <= spawnChance - 5)
				{
					line.push_back(bedrock);
				}
				else if(num <= spawnChance - 3)
				{
					line.push_back(lava);
				}
				else if(num <= spawnChance - 1)
				{
					line.push_back(water);
				}
			}
		}
		/// Reduce spawn chance value, to a minimum of 300, increasing frequency of which rarer blocks spawn
		spawnChance = max(spawnChance - 2.0f, 300.0f);

		/// Add the line to the map
		map.push_back(line);
	}
}

ObjectManager::~ObjectManager(void)
{

}

void ObjectManager::update(float timeElapsed)
{
	/// Increases the players y value based on acceleration. 
	//m_playerOne.getPosition().y  += min(max(accel * timeElapsed, -10.0f), 10.0f);
	m_playerOne.Update(accel, timeElapsed);
	/// A boolean which tracks if the player has struck a body which is not liquid
	bool struck = false;

	/// If the player presses A or the Left Arrow Key
	if(KeyManager::getManager()->keyDown(SDL_SCANCODE_A) || KeyManager::getManager()->keyDown(SDL_SCANCODE_LEFT))
	{
		/// Move the player to the left
		m_playerOne.MoveLeft(timeElapsed, timeTillMoveCounter);

		/// Check every position in a 2 block radius around the player
		for(int i = max(0, (int)((m_playerOne.getPosition().y  - 32) / size) - lineDel); i < min((int)map.size(), (int)((m_playerOne.getPosition().y  + 64) / size) - lineDel); i++)
		{
			for(int k = max(0, (int)((m_playerOne.getPosition().x - 32) / size)); k < min((int)map.at(i).size(), (int)((m_playerOne.getPosition().x + 64) / size)); k++)
			{
				/// If the current square is mud
				if(map.at(i).at(k) == mud)
				{
					/// Check if the block is within the player bounds
					if(m_playerOne.CheckBlock(mud, lineDel, 0, k, i))
					{
						/// Destroy the block
						map.at(i).at(k) = none;
					}
				}
				/// If the current sqaure is gold
				else if(map.at(i).at(k) == gold)
				{ 
					/// Check if the block is within the player bounds
					if(m_playerOne.CheckBlock(gold, lineDel, 0, k, i))
					{
						/// Destroy the block and increase score
						map.at(i).at(k) = none;						
					}
				}
				/// If the current square is water
				else if(map.at(i).at(k) == water)
				{
					/// Check if the block is within the player bounds
					if(m_playerOne.CheckBlock(water, lineDel, 0, k, i))
					{
						/// Destroy the block and heal the player
						map.at(i).at(k) = none;
					}
				}
				/// If the current square is bedrock
				else if(map.at(i).at(k) == bedrock)
				{
					/// Check if the block is within the player bounds
					m_playerOne.CheckBlock(bedrock, lineDel, 0, k, i);
				}
			}
		}
	}
	/// If the player presses D or Right Arrow key, move the player to the right
	if(KeyManager::getManager()->keyDown(SDL_SCANCODE_D) || KeyManager::getManager()->keyDown(SDL_SCANCODE_RIGHT))
	{
		m_playerOne.MoveRight(timeElapsed, timeTillMoveCounter);

		/// Check every position in a 2 block radius around the player and interact with the blocks accordingly
		for(int i = max(0, (int)((m_playerOne.getPosition().y  - 32) / size) - lineDel); i < min((int)map.size(),(int)((m_playerOne.getPosition().y  + 64) / size) - lineDel); i++)
		{
			for(int k = max(0, (int)((m_playerOne.getPosition().x - 32) / size)); k < min((int)map.at(i).size(), (int)((m_playerOne.getPosition().x + 64) / size)); k++)
			{
				if(map.at(i).at(k) == mud)
				{
					if(m_playerOne.CheckBlock(mud, 0, lineDel, k, i))
					{
						map.at(i).at(k) = none;
					}
				}
				else if(map.at(i).at(k) == gold)
				{
					if(m_playerOne.CheckBlock(gold, 0, lineDel, k, i))
					{
						map.at(i).at(k) = none;
					}
				}
				else if(map.at(i).at(k) == water)
				{
					if(m_playerOne.CheckBlock(water, 0, lineDel, k, i))
					{
						map.at(i).at(k) = none;
					}
				}
				else if(map.at(i).at(k) == bedrock)
				{
					m_playerOne.CheckBlock(bedrock, 0, lineDel, k, i);
				}
			}
		}
	}
	/// If the player presses the S or Down Arrow keys, destroy blocks beneath the player
	if(KeyManager::getManager()->keyDown(SDL_SCANCODE_S)||KeyManager::getManager()->keyDown(SDL_SCANCODE_DOWN))
	{
		for(int i = max(0, (int)((m_playerOne.getPosition().y  + 32) / size) - lineDel); i < min((int)map.size(), (int)((m_playerOne.getPosition().y  + 64) / size) - lineDel); i++)
		{
			for(int k = max(0, (int)((m_playerOne.getPosition().x - 32) / size)); k < min((int)map.at(i).size(), (int)((m_playerOne.getPosition().x + 64) / size)); k++)
			{
				if(map.at(i).at(k) == mud)
				{
					if(m_playerOne.CheckBlock(mud, 1, lineDel, k, i))
					{
						map.at(i).at(k) = none;
					}
				}
				if(map.at(i).at(k) == gold)
				{
					if(m_playerOne.CheckBlock(gold, 1, lineDel, k, i))
					{
						map.at(i).at(k) = none;
					}
				}
				if(map.at(i).at(k) == water)
				{
					if(m_playerOne.CheckBlock(water, 1, lineDel, k, i))
					{
						map.at(i).at(k) = none;
					}
				}
			}
		}
	}	
	/// If the player presses the W or Up Arrow keys
	if(KeyManager::getManager()->keyDown(SDL_SCANCODE_W) || KeyManager::getManager()->keyDown(SDL_SCANCODE_UP))
	{
		/// If the player is on the ground and not moving
		if(accel == 0)
		{
			/// Increase acceleration upwards
			accel =- 100 / max(timeTillMoveCounter, 0.5f);
		}
	}
	/// Check every block in a 2 block radius around the player
	for(int i = max(0, (int)((m_playerOne.getPosition().y  - 32) / size) - lineDel); i < min((int)map.size(), (int)((m_playerOne.getPosition().y  + 64) / size) - lineDel); i++)
	{
		for(int k = max(0, (int)((m_playerOne.getPosition().x - 32) / size)); k < min((int)map.at(i).size(), (int)((m_playerOne.getPosition().x + 64) / size)); k++)
		{
			/// If the block is mud 
			if(map.at(i).at(k) == mud)
			{
				/// If the player has collided with the block
				if(m_playerOne.CheckBlock(mud, 2, lineDel, k, i))
				{
					/// If the block is on top of the player
					if(m_playerOne.getPosition().y  + (size / 2) > ((i + lineDel) * size))
					{
						/// Delete the block
						map.at(i).at(k) = none;
					}
					else
					{
						/// Stop the player and move them on top of the block
						m_playerOne.Land(i, lineDel);
						struck = true;
					}
				}
			}
			/// If the block is gold
			else if(map.at(i).at(k) == gold)
			{
				/// If the player has collided with the block
				if(m_playerOne.CheckBlock(gold, 2, lineDel, k, i))
				{
					/// If the block is on top of the player
					if(m_playerOne.getPosition().y + (size / 2) > ((i + lineDel) * size))
					{
						/// Delete the block and update the score by 10
						map.at(i).at(k) = none;
					}
					else
					{
						/// Stop the player and move them on top of the block
						m_playerOne.Land(i, lineDel);
						struck = true;
					}
				}
			}
			/// If the block is water
			else if(map.at(i).at(k) == water)
			{
				/// If the player has collided with the block
				if(m_playerOne.CheckBlock(water, 2, lineDel, k, i))
				{
					/// Remove the water and increase health
					map.at(i).at(k) = none;
				}
			}
			/// If the block is bedrock
			else if(map.at(i).at(k) == bedrock)
			{
				/// If the player has collided with the block
				if(m_playerOne.CheckBlock(bedrock, 2, lineDel, k, i))
				{
					/// If it is above the player
					if(m_playerOne.getPosition().y  + (size / 2) > ((i + lineDel) * size))
					{
						/// Stop the player and position him under the block
						struck = true;
					}
					else
					{
						/// Stop the player and position him over the block
						m_playerOne.Land(i, lineDel);
						struck = true;
					}
				}
			}
			/// If the block is lava
			else if(map.at(i).at(k) == lava)
			{
				/// If the player has collided with the block
				if(m_playerOne.CheckBlock(lava, 2, lineDel, k, i))
				{
					/// Decrease player health
					health -= 10 * timeElapsed;
				}
			}
		}
	}		

	/// Attempt to spawn another row of terrain
	spawnTerrain();

	/// Delete the top row of the map once the player gets far enough away
	if(map.size() > 2000 / size)
	{
		map.erase(map.begin() + 1);
		lineDel += 1;
	}

	///Increase acceleration
	accel += 98 * timeElapsed / max(timeTillMoveCounter, 0.5f);

	/// If any movement key is pressed, change the currently displayed texture
	if(KeyManager::getManager()->keyDown(SDL_SCANCODE_A)||KeyManager::getManager()->keyDown(SDL_SCANCODE_D)||
		KeyManager::getManager()->keyDown(SDL_SCANCODE_W)||KeyManager::getManager()->keyDown(SDL_SCANCODE_S)||
		KeyManager::getManager()->keyDown(SDL_SCANCODE_LEFT)||KeyManager::getManager()->keyDown(SDL_SCANCODE_RIGHT)||
		KeyManager::getManager()->keyDown(SDL_SCANCODE_UP)||KeyManager::getManager()->keyDown(SDL_SCANCODE_DOWN))
	{
		textureChange -= timeElapsed * 5;
		if(textureChange <= 0)
		{
			playerTex = (playerTex + 1) % 2;
			textureChange = max(timeTillMoveCounter, 0.3f);
		}
		if(KeyManager::getManager()->keyDown(SDL_SCANCODE_S)||KeyManager::getManager()->keyDown(SDL_SCANCODE_DOWN))
		{
			texNum = falling;
			if(KeyManager::getManager()->keyDown(SDL_SCANCODE_A)||KeyManager::getManager()->keyDown(SDL_SCANCODE_D)||
				KeyManager::getManager()->keyDown(SDL_SCANCODE_LEFT)||KeyManager::getManager()->keyDown(SDL_SCANCODE_RIGHT))
			{
				texNum = floating;
			}

		}
		else if(KeyManager::getManager()->keyDown(SDL_SCANCODE_W)||KeyManager::getManager()->keyDown(SDL_SCANCODE_UP))
		{
			texNum = upSide;
		}
		else if(KeyManager::getManager()->keyDown(SDL_SCANCODE_A)||KeyManager::getManager()->keyDown(SDL_SCANCODE_D)||
			KeyManager::getManager()->keyDown(SDL_SCANCODE_LEFT)||KeyManager::getManager()->keyDown(SDL_SCANCODE_RIGHT))
		{
			texNum = side;
		}
	}
	
	if(struck)
	{
		accel = 0;
		if(texNum == falling)
		{
			texNum = down;
		}
		else if(texNum == floating)
		{
			texNum = downSide;
		}
		else if(texNum == upSide)
		{
			texNum = side;
		}
	}
}


void ObjectManager::LavaUpdate(float timeElapsed)
{
	/// Updates check for a lava movement
	timeTillMove -= timeElapsed;
	/// If the lava is ready to be moved
	if(timeTillMove <= 0)
	{
		/// Reset the movement timer to the current max movement timer
		timeTillMove = timeTillMoveCounter;
		/// Update the movement timer to be faster
		timeTillMoveCounter = max(timeTillMoveCounter - 0.25, 0.1);

		/// Check every square in the map
		for(int i = 0; i < map.size(); i++)
		{
			for(int k = 0; k < map.at(i).size(); k++)
			{
				/// If the current square is lava
				if(map.at(i).at(k)==lava)
				{
					/// Temporarily store all blocks surrounding the lava
					int left = max(0, k - 1);
					int right = min((int)map.at(i).size() - 1, k + 1);
					int up  =  max(0, i - 1);
					int down = min((int)map.size() - 1, i + 1);


					/// If there's currently no block above the current block
					if(map.at(up).at(k) == none)
					{
						/// Put a magma square above the current block
						map.at(up).at(k) = magma;
					}
					/// Otherwise if the block above the current block is water
					else if(map.at(up).at(k) == water)
					{
						/// Turn the water in to bedrock
						map.at(up).at(k) = bedrock;
					}

					/// If there's currently no block below the current block
					if(map.at(down).at(k) == none)
					{
						/// Put a flow block below the current block
						map.at(down).at(k) = flow;
					}
					/// Otherwise if the block below the current block is water
					else if(map.at(down).at(k) == water)
					{
						/// Turn the water block in to bedrock
						map.at(down).at(k) = bedrock;
					}
					/// Otherwise check to the left and right
					else
					{
						/// If there is currently no block to the left of the current block
						if(map.at(i).at(left) == none)
						{
							if(map.at(down).at(left) == lava || map.at(down).at(left) == magma
							|| map.at(down).at(left) == mud || map.at(down).at(left) == gold
							|| map.at(down).at(left) == bedrock || map.at(down).at(k) == mud
							|| map.at(down).at(k) == gold || map.at(down).at(k) == bedrock)
							{
								/// Place a lava block 
								map.at(i).at(left) = lava;
							}
						}
						/// If the block is water
						else if(map.at(i).at(left) == water)
						{
							/// Turn the water block in to bedrock
							map.at(i).at(left) = bedrock;
						}

						/// If there is currently no block to the right of the current block
						if(map.at(i).at(right) == none)
						{
							if(map.at(down).at(right) == lava || map.at(down).at(right) == magma
							|| map.at(down).at(right) == mud || map.at(down).at(right) == gold
							|| map.at(down).at(right) == bedrock || map.at(down).at(k) == mud
							|| map.at(down).at(k) == gold || map.at(down).at(k) == bedrock)
							{
								/// Place a magma block to be turned in to a lava block later in the iteration
								map.at(i).at(right) = magma;
							}
						}		
						/// If the block is water
						else if(map.at(i).at(right) == water)
						{
							/// Turn the block in to bedrock
							map.at(i).at(right) = bedrock;
						}
					}					
				}
				else if(map.at(i).at(k) == flow)
				{
					/// Store all blocks surrounding the current block
					int left = max(0, k - 1);
					int right = min((int)map.at(i).size() - 1, k + 1);
					int up = max(0, i - 1);
					int down = min((int)map.size() - 1, i + 1);

					/// Turn the flow block in to lava
					map.at(i).at(k) = lava;
					
					/// If the block above the current block is empty
					if(map.at(up).at(k) == none)
					{
						/// Place a magma block above the current block
						map.at(up).at(k) = magma;
					}
					/// If the block below the current block is empty
					if(map.at(down).at(k) == none)
					{
						/// Place a magma block to be turned in to a lava block later in the iteration
						map.at(down).at(k) = magma;
					}
					/// Otherwise check to the left and right of the current block
					else
					{
						/// If there is currently no block to the left of the current block
						if(map.at(i).at(left) == none)
						{
							if(map.at(down).at(left) == lava || map.at(down).at(left) == magma
							|| map.at(down).at(left) == mud || map.at(down).at(left) == gold
							|| map.at(down).at(left) == bedrock || map.at(down).at(k) == mud
							|| map.at(down).at(k) == gold || map.at(down).at(k) == bedrock)
							{
								/// Place a lava block
								map.at(i).at(left) = lava;
							}
						}
						/// If there is currently no block to the right of the current block
						if(map.at(i).at(right) == none)
						{
							if(map.at(down).at(right) == lava || map.at(down).at(right) == magma
							|| map.at(down).at(right) == mud || map.at(down).at(left) == gold
							|| map.at(down).at(left) == bedrock || map.at(down).at(k) == mud
							|| map.at(down).at(k) == gold || map.at(down).at(k) == bedrock)
							{
								/// Place a magma block to be turned in to a lava block later in the iteration
								map.at(i).at(right) = magma;
							}
						}
					}
				}
				/// If the current block is magma
				else if(map.at(i).at(k) == magma)
				{
					/// Turn it in to lava
					map.at(i).at(k) = lava;
				}
			}
		}
	}
}

void ObjectManager::draw(SDL_Renderer* renderer)
{
	SDL_Rect pos;
	pos.w = size;
	pos.h = size;

	for(int i = max(0, (int)((m_playerOne.getPosition().y  - 400) / size) - lineDel); i < min((int)map.size(), (int)((m_playerOne.getPosition().y  + 400) / size) - lineDel); i++)
	{
		pos.y = ((i + lineDel) * size) - m_playerOne.getPosition().y  + 360;
		for(int k = 0; k < map.at(i).size(); k++)
		{
			if(map.at(i).at(k) == mud)
			{
				pos.x = (k * size);
				SDL_RenderCopyEx(renderer, TextureManager::getManager()->wall->getTexture(), nullptr, &pos, 0, nullptr, SDL_RendererFlip::SDL_FLIP_NONE);
			}
			else if(map.at(i).at(k) == magma)
			{
				pos.x = (k*size);
				SDL_RenderCopyEx(renderer, TextureManager::getManager()->magma->getTexture(), nullptr, &pos, 0, nullptr, SDL_RendererFlip::SDL_FLIP_NONE);
			}
			else if(map.at(i).at(k) == lava)
			{
				pos.x = (k * size);
				SDL_RenderCopyEx(renderer, TextureManager::getManager()->lava->getTexture(), nullptr, &pos, 0, nullptr, SDL_RendererFlip::SDL_FLIP_NONE);
			}
			else if(map.at(i).at(k) == gold)
			{
				pos.x = (k * size);
				SDL_RenderCopyEx(renderer, TextureManager::getManager()->gold->getTexture(), nullptr, &pos, 0, nullptr, SDL_RendererFlip::SDL_FLIP_NONE);
			}
			else if(map.at(i).at(k) == water)
			{
				pos.x = (k * size);
				SDL_RenderCopyEx(renderer, TextureManager::getManager()->water->getTexture(), nullptr, &pos, 0, nullptr, SDL_RendererFlip::SDL_FLIP_NONE);
			}
			else if(map.at(i).at(k) == bedrock)
			{
				pos.x = (k * size);
				SDL_RenderCopyEx(renderer, TextureManager::getManager()->bedrock->getTexture(), nullptr, &pos, 0, nullptr, SDL_RendererFlip::SDL_FLIP_NONE);
			}
		}
	}

	pos.x = m_playerOne.getPosition().x;
	pos.y = m_playerOne.getPosition().y -m_playerOne.getPosition().y +360;
	pos.w = 32;
	pos.h = 32;
	SDL_RenderCopyEx(renderer, TextureManager::getManager()->miners->at(texNum + playerTex)->getTexture(), nullptr, &pos, 0, nullptr, (SDL_RendererFlip)(int)flip);		
	
	TextureManager::getManager()->drawText(renderer, "Score: " + std::to_string(m_playerOne.getScore()), 20, 20, TextureManager::positioning::left);
	TextureManager::getManager()->drawText(renderer, "Health: " + std::to_string((int)max(m_playerOne.getHealth(), 0.0f)), Constants::SCREEN_WIDTH - 20, 20, TextureManager::positioning::right);	
	TextureManager::getManager()->drawText(renderer, "Distance: " + std::to_string((int)m_playerOne.getPosition().y ), Constants::SCREEN_WIDTH / 2 , 20, TextureManager::positioning::center);
}


void ObjectManager::setUp()
{
	/// Reinitialise all changed variables
	playerPos = Vector2f(Constants::SCREEN_WIDTH / 2, 0);
	accel = 0;
	score = 0;
	health = 100;
	spawnChance = 600;
	lineDel = 0;
	timeTillMove = 0;
	timeTillMoveCounter = 2;
	/// Clear the map vector
	map = vector<vector<short>>();
	/// Spawn a new set of blocks
	for(int k = 0; k < (Constants::SCREEN_HEIGHT * 2) / size; k++)
	{
		spawnTerrain();
	}
	
}