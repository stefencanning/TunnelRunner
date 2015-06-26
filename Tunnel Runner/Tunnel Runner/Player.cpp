#include "Player.h"

Player::Player(Vector2f pos) : m_position(pos), m_flip(false), m_health(100), m_score(0), m_waterHeal(5)
{
}

Player::~Player(void)
{
}

Vector2f Player::getPosition(){	return m_position; }
float Player::getHealth(){ return m_health; }
int Player::getScore(){	return m_score; }

void Player::Update(float accel, float t)
{
	/// Increases the players y value based on acceleration. 
	m_position.y += min(max(accel * t, -10.0f), 10.0f);	
}

void Player::MoveLeft(float t, float timeTillMoveCounter)
{
	m_flip = true;
	m_position.x = max(0.0f, m_position.x - min(120 * t / max(timeTillMoveCounter, 0.5f), 15.0f));
}

void Player::MoveRight(float t, float timeTillMoveCounter)
{
	m_flip = false;
	m_position.x = min(Constants::SCREEN_WIDTH - 32.0f, m_position.x + min(120 * t / max(timeTillMoveCounter, 0.5f), 15.0f));	
}

bool Player::CheckBlock(int type, int dir, int lineDel, int xIndex, int yIndex)
{
	if(CheckBounds(lineDel, dir, xIndex, yIndex))
	{
		switch(type){
		case(5):
			/// On hitting bedrock
			if(dir == 0)
			{
				if(m_flip)
				{
					m_position.x = (xIndex + 1) * Constants::BLOCK_SIZE;
				}			
				else
				{
					m_position.x = (xIndex * Constants::BLOCK_SIZE) - Constants::PLAYER_SIZE;
				}
			}
			break;
		case(6):
			/// On hitting gold
			if(dir != 2)
			{
				m_score += 10;
			}
			break;
		case(7):
			/// On hitting water
			m_health = min(100, (int)m_health + m_waterHeal);
			break;
		}
		return true;
	}
	return false;
}

bool Player::CheckBounds(int lineDel, int dir, int xIndex, int yIndex)
{
	/// Side check
	if(dir == 0)
	{
		if(m_position.x + Constants::PLAYER_SIZE > xIndex * Constants::BLOCK_SIZE 
		&& m_position.x < (xIndex + 1) * Constants::BLOCK_SIZE 
		&& m_position.y + Constants::PLAYER_SIZE - (Constants::BLOCK_SIZE / 4) > (yIndex + lineDel) * Constants::BLOCK_SIZE 
		&& m_position.y + (Constants::BLOCK_SIZE / 4) < ((yIndex + 1) + lineDel) * Constants::BLOCK_SIZE)
		{
			return true;
		}
	}
	/// Digging down check
	else if(dir == 1)
	{
		if(m_position.x + Constants::PLAYER_SIZE > xIndex * Constants::BLOCK_SIZE 
		&& m_position.x < (xIndex + 1) * Constants::BLOCK_SIZE
		&& m_position.y + Constants::PLAYER_SIZE + (Constants::BLOCK_SIZE / 2) > (yIndex + lineDel) * Constants::BLOCK_SIZE
		&& m_position.y < ((yIndex + 1) + lineDel) * Constants::BLOCK_SIZE)
		{
			return true;
		}
	}
	/// Falling down check
	else if(dir == 2)
	{
		if(m_position.x + Constants::PLAYER_SIZE > (xIndex * Constants::BLOCK_SIZE) 
		&& m_position.x < (xIndex + 1) * Constants::BLOCK_SIZE 
		&& m_position.y + Constants::PLAYER_SIZE > (yIndex + lineDel) * Constants::BLOCK_SIZE  
		&& m_position.y < ((yIndex + 1) + lineDel) * Constants::BLOCK_SIZE)
		{
			return true;
		}
	}
	return false;
}

void Player::Land(int yIndex, int curDepth)
{
	m_position.y = (yIndex + curDepth) * Constants::BLOCK_SIZE - Constants::PLAYER_SIZE;
}

void Player::Draw()
{

}
