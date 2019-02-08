#pragma once

class Player
{
public:
	Player();
	~Player();
	Player(const Player& p_other);

	int getHealth();
	void setHealth(int p_health);
	int getScore();
	void setScore(int p_score);

private:
	int health;
	int score;
};
