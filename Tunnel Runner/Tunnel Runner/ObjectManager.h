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
	int waterHeal;
	ObjectManager(void);
	~ObjectManager(void);
	void init();
	void update(float timeElapsed);
	void draw(SDL_Renderer* renderer);
	static ObjectManager* getManager();
	Vector2f playerPos;
	float accel;
	int score;
	float health;
	int lineDel;
	float spawnChance;
	float timeTillMove;
	float timeTillMoveCounter;
	float textureChange;
	vector<vector<short>> map;
	void LavaUpdate(float timeElapsed);
	void setUp();
	int playerTex;
	int texNum;
	bool flip;
	void spawnTerrain();
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
};
#endif

