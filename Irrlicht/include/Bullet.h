#pragma once

class Bullet
{
public:
	Bullet(int p_damage, float p_speed, vector3df& p_vec, IBillboardSceneNode* p_node);
	~Bullet();

	IBillboardSceneNode * getNode();

	vector3df& getVec();

private:
	int damage;
	float speed;
	IBillboardSceneNode* node;
	vector3df vec;
};

