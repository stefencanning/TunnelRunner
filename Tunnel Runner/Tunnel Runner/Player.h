#pragma once

#include "Vector2f.h"
#include "Constants.h"
#include <vector>

using namespace std;

class Player
{
public:
	Player(Vector2f pos);
	~Player(void);

	/// Get Methods
	Vector2f getPosition();
	int getScore();
	float getHealth();
	void setPosition(Vector2f pos){m_position = pos;};
	void setScore(int score){m_score = score;};
	void setHealth(float health){m_health = health;};
	void updatePosition(Vector2f pos){m_position += pos;};
	void updateScore(int score){m_score += score;};
	void updateHealth(float health){m_health += health;};

	/// Update the player position
	void Update(float accel, float t);

	/// Move the player to the left
	void MoveLeft(float t, float timeTillMoveCounter);

	/// Move the player to the right
	void MoveRight(float t, float timeTillMoveCounter);

	/// Check for collision with a block
	bool CheckBlock(int type, int dir, int xIndex, int yIndex, int lineDel);
	
	void Land(int yIndex, int curDepth);

	/// Method to draw player to screen
	void Draw();
	bool getFlip(){return m_flip;};

private:
	bool m_flip;
	int m_score;	
	int m_waterHeal;
	float m_health;
	Vector2f m_position;

	/// Check bounds method
	bool CheckBounds(int xIndex, int yIndex, int dir, int lineDel);
};

