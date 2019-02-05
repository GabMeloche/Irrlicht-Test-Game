#pragma once

class Player
{
private:
	int health;
public:
	Player();
	~Player();
	Player(const Player& p_other);

	int getHealth();
	void setHealth(int p_health);
};
