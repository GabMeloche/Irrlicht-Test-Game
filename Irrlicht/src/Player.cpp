#include <Player.h>

Player::Player()
{
	health = 100;
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
