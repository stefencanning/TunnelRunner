#include "SceneManager.h"

SceneManager* SceneManager::me;
SceneManager* SceneManager::getManager()
{
	if(!me)
	{
		me= new SceneManager();
	}
	return me;
}


SceneManager::SceneManager(void)
{
	game = new Game();
}


SceneManager::~SceneManager(void)
{
	delete game;
}

void SceneManager::update(float timeElapsed)
{
	game->update(timeElapsed);
}

void SceneManager::draw(SDL_Renderer* renderer)
{
	game->draw(renderer);
}