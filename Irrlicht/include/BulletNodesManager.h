#pragma once
#include <vector>
#include <Scene.h>
#include <irrlicht.h>
#include <EventReceiver.h>
#include <Player.h>
#include <IBillboardSceneNode.h>
#include <Bullet.h>

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

class BulletNodesManager
{
public:
	BulletNodesManager();
	~BulletNodesManager();

	void createBullet(ISceneManager* smgr, IVideoDriver* driver);
	void addBullet(IBillboardSceneNode* bullet, vector3df& vec);
	void removeBullet(IBillboardSceneNode* bullet);
	int getBulletsShot();
	Bullet& operator[](unsigned int i);
private:
	unsigned int bulletsShot;
	std::vector<Bullet> bullets;
};

