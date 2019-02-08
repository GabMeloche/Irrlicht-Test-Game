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

class Enemy
{
public:
	Enemy(ISceneManager* smgr, IVideoDriver* driver);
	~Enemy();
	void setRandomPos();
	IAnimatedMeshSceneNode* getNode();

private:
	IAnimatedMeshSceneNode* node;
	IAnimatedMesh* mesh;
};

