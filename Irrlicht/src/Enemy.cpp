#include <Enemy.h>
#include <irrlicht.h>
#include <EventReceiver.h>
#include <Scene.h>
#include <Player.h>
#include <iostream>
#include <Bullet.h>
#include <BulletNodesManager.h>
#include <cassert>
#include <cstdlib> 
#include <ctime>

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

enum
{
	ID_IsNotPickable = 0,
	IDFlag_IsPickable = 1 << 0,
	IDFlag_IsHighlightable = 1 << 1
};

Enemy::Enemy(ISceneManager* smgr, IVideoDriver* driver)
{
	SMaterial material;
	mesh = smgr->getMesh("res/media/sydney.md2");

	assert(mesh);

	node = smgr->addAnimatedMeshSceneNode(mesh, 0, IDFlag_IsPickable | IDFlag_IsHighlightable);

	if (node)
	{
		setRandomPos();
		node->setScale(core::vector3df(1.5f));
		node->setMD2Animation(scene::EMAT_STAND);
		material.setTexture(0, driver->getTexture("res/media/sydney.bmp"));
		material.Lighting = true;
		material.NormalizeNormals = true;
		node->getMaterial(0) = material;

		scene::ITriangleSelector* selector = smgr->createTriangleSelector(node);
		node->setTriangleSelector(selector);
		selector->drop();

		node->setMaterialFlag(EMF_LIGHTING, false);
		node->setMaterialTexture(0, driver->getTexture("res/media/sydney.bmp"));

		const core::aabbox3d<f32>& box = node->getBoundingBox();
		core::vector3df radius = box.MaxEdge - box.getCenter();

		//This part should make Sydney collidable, but doesn't really work yet
		/*scene::ISceneNodeAnimator* anim = smgr->createCollisionResponseAnimator(
			selector, node, radius,
			core::vector3df(0, -10, 0), core::vector3df(0, 0, 0));
		node->addAnimator(anim);
		selector->drop();
		anim->drop();*/
	}
}

Enemy::~Enemy()
{
	//node->drop();
}

void Enemy::setRandomPos()
{
	srand((unsigned)time(0));

	int random = rand() % 5;
	vector3df randomPos;

	switch (random)
	{
	case 0:
		randomPos = vector3df(-320.0f, 100.0f, 210.0f);
		break;

	case 1:
		randomPos = vector3df(50.0f, 170.0f, -920.0f);
		break;

	case 2:
		randomPos = vector3df(600.0f, -23.0f, -40.0f);
		break;

	case 3:
		randomPos = vector3df(600.0f, 100.0f, -40.0f);
		break;

	case 4:
		randomPos = vector3df(600.0f, 100.0f, -440.0f);
		break;

	default:
		randomPos = vector3df(-90.0f, -23.0f, 20.0f);
		break;
	}
	node->setPosition(randomPos);
}

IAnimatedMeshSceneNode * Enemy::getNode()
{
	return node;
}


