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
	void addBullet(IBillboardSceneNode* bullet);
	void removeBullet(int index);
	void moveBullets(ISceneManager* smgr);
	int getBulletsShot();
	void setSmgr(ISceneManager * p_smgr);
	Bullet& operator[](unsigned int i);

private:
	unsigned int bulletsShot;
	ISceneManager* smgr;
	std::vector<Bullet> bullets;
};

