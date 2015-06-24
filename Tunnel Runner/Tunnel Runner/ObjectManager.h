#pragma once
#ifndef OBJECTMANAGER_H
#define OBJECTMANAGER_H
#include <vector>
#include <time.h>
#include "TextureManager.h"
#include "KeyManager.h"
using namespace std;
class ObjectManager
{
private:
	static ObjectManager* me;
	/// Checks if a new row is needed to be spawned, and then spawns it if true
	void spawnTerrain();

public:
	const short none;
	const short mud;
	const short magma;
	const short lava;
	const short flow;
	const short bedrock;
	const short gold;
	const short water;
	const short size;
	bool flip;
	int waterHeal;
	int score;
	int playerTex;
	int texNum;
	int lineDel;
	float accel;
	float health;
	float spawnChance;
	float timeTillMove;
	float timeTillMoveCounter;
	float textureChange;	
	Vector2f playerPos;
	vector<vector<short>> map;	
	enum dirs
	{
		down=0,
		downSide=2,
		side=4,
		up=6,
		upSide=8,
		falling=10,
		floating=12
	};	

	/// Initialises the object manager variables as default and spawns the first set of blocks
	ObjectManager(void);
	/// Deconstructor
	~ObjectManager(void);
	/// Restarts the map for a new run
	void setUp();
	/// Updates the player and calls update methods
	void update(float timeElapsed);
	/// Draws all entities to the screen
	void draw(SDL_Renderer* renderer);
	/// Gets a single instance of the ObjectManager
	static ObjectManager* getManager();
	/// Updates the lava flow to spread the lava
	void LavaUpdate(float timeElapsed);
	
	
};
#endif

