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

Bullet::Bullet(int p_damage, float p_speed, vector3df& p_vec, IBillboardSceneNode* p_node)
{
	damage = p_damage;
	speed = p_speed;
	vec = p_vec;
	node = p_node;

}


Bullet::~Bullet()
{
}

IBillboardSceneNode* Bullet::getNode()
{
	return node;
}

vector3df& Bullet::getVec()
{
	return vec;
}