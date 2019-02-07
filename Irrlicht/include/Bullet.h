#pragma once
#include <irrlicht.h>
#include <EventReceiver.h>
#include <Scene.h>
#include <Player.h>
#include <iostream>
#include <Bullet.h>
#include <BulletNodesManager.h>

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

class Bullet
{
public:
	Bullet(int p_damage, float p_speed, line3d<f32>& p_ray, IBillboardSceneNode* p_node);
	~Bullet();

	IBillboardSceneNode * getNode();

	vector3df& getVec();

	void addDistance();

	float getSpeed();
	float getDistance();
	vector3df& getVector();
	line3d<f32>& getRay();

	void setVector(vector3df& p_vec);
	void setRay(line3d<f32>& p_ray);
	
private:
	int damage;
	float distance;
	float speed;
	vector3df vec;
	line3d<f32> ray;
	IBillboardSceneNode* node;
	ISceneNodeAnimator* anim;
};

