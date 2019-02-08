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

Bullet::Bullet(int p_damage, float p_speed, line3d<f32>& p_ray, IBillboardSceneNode* p_node)
{
	damage = p_damage;
	distance = 0.0f;
	speed = p_speed;
	ray = p_ray;
	vec = ray.getVector().normalize();
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

float Bullet::getSpeed()
{
	return speed;
}

float Bullet::getDistance()
{
	return distance;
}

void Bullet::addDistance()
{
	distance += speed;
}

vector3df & Bullet::getVector()
{
	return vec;
}

line3d<f32>& Bullet::getRay()
{
	return ray;
}

void Bullet::setVector(vector3df & p_vec)
{
	vec = p_vec;
}

void Bullet::setRay(line3d<f32>& p_ray)
{
	ray = p_ray;
}
