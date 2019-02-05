#include <Scene.h>
#include <irrlicht.h>
#include <EventReceiver.h>
#include <Player.h>

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

enum
{
	// I use this ISceneNode ID to indicate a scene node that is
	// not pickable by getSceneNodeAndCollisionPointFromRay()
	ID_IsNotPickable = 0,

	// I use this flag in ISceneNode IDs to indicate that the
	// scene node can be picked by ray selection.
	IDFlag_IsPickable = 1 << 0,

	// I use this flag in ISceneNode IDs to indicate that the
	// scene node can be highlighted.  In this example, the
	// homonids can be highlighted, but the level mesh can't.
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
		// We're not done with this selector yet, so don't drop it.
	}
	//CAMERA SETUP
	scene::ICameraSceneNode* camera =
		smgr->addCameraSceneNodeFPS(0, 100.0f, .3f, ID_IsNotPickable, 0, 0, true, 3.f);
	camera->setPosition(core::vector3df(50, 50, -60));
	camera->setTarget(core::vector3df(-70, 30, -60));

	if (selector)
	{
		scene::ISceneNodeAnimator* anim = smgr->createCollisionResponseAnimator(
			selector, camera, core::vector3df(30, 50, 30),
			core::vector3df(0, -10, 0), core::vector3df(0, 30, 0));
		selector->drop(); // As soon as we're done with the selector, drop it.
		camera->addAnimator(anim);
		anim->drop();  // And likewise, drop the animator when we're done referring to it.
	}
}


Scene::~Scene()
{
	smgr->clear();
}

ISceneManager* Scene::getSmgr()
{
	return smgr;
}