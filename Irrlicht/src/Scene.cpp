#include <Scene.h>
#include <irrlicht.h>
#include <EventReceiver.h>
#include <Player.h>
#include <IBillboardSceneNode.h>

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

Scene::Scene(IrrlichtDevice* p_device)
{
	smgr = p_device->getSceneManager();
	p_device->getFileSystem()->addFileArchive("res/media/map-20kdm2.pk3");
	mapMesh = smgr->getMesh("20kdm2.bsp");
	mapNode = 0;

	// The Quake mesh is pickable, but doesn't get highlighted.
	if (mapMesh)
		mapNode = smgr->addOctreeSceneNode(mapMesh->getMesh(0), 0, IDFlag_IsPickable);

	scene::ITriangleSelector* selector = 0;

	if (mapNode)
	{
		mapNode->setPosition(core::vector3df(-1350, -130, -1400));
		selector = smgr->createOctreeTriangleSelector(
			mapNode->getMesh(), mapNode, 128);
		mapNode->setTriangleSelector(selector);
	}

	//CAMERA SETUP
	scene::ICameraSceneNode* camera =
		smgr->addCameraSceneNodeFPS(0, 100.0f, 0.3f, ID_IsNotPickable, 0, 0, true, 3.0f);
	camera->setPosition(core::vector3df(50, 50, -60));
	camera->setTarget(core::vector3df(-70, 30, -60));

	if (selector)
	{
		scene::ISceneNodeAnimator* anim = smgr->createCollisionResponseAnimator(
			selector, camera, core::vector3df(30, 40, 30),
			core::vector3df(0, -10, 0), core::vector3df(0, 30, 0));
		selector->drop();
		camera->addAnimator(anim);
		anim->drop();
	}
}


Scene::~Scene()
{
	if (mapMesh)
		mapMesh->drop();
	if (mapNode)
		mapNode->drop();
	if (billboardNode)
		billboardNode->drop();
	if (billboardMesh)
		billboardMesh->drop();
	if (smgr)
	{
		smgr->clear();
		smgr->drop();
	}
}

ISceneManager* Scene::getSmgr()
{
	return smgr;
}

IBillboardSceneNode* Scene::getBillboardNode()
{
	return billboardNode;
}

void Scene::setBillboardPos(core::vector3df pos)
{
	billboardNode->setPosition(pos);
}