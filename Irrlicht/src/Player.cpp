#include <Player.h>

Player::Player()
{
	health = 100;
	score = 0;
}

Player::~Player()
{
}

Player::Player(const Player & p_other)
{
	health = p_other.health;
}

int Player::getHealth()
{
	return health;
}

void Player::setHealth(int p_health)
{
	health = p_health;
}

int Player::getScore()
{
	return score;
}

void Player::setScore(int p_score)
{
	score = p_score;
}
