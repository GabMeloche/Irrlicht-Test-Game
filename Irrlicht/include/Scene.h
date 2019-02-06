#pragma once
#include <irrlicht.h>
#include <EventReceiver.h>
#include <Player.h>

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

class Scene
{
public:
	Scene(IrrlichtDevice* p_device);
	~Scene();

	ISceneManager* getSmgr();
	IBillboardSceneNode* getBillboardNode();
	void setBillboardPos(core::vector3df pos);
private:
	ISceneManager* smgr;
	IAnimatedMesh* mapMesh;
	IMeshSceneNode* mapNode;
	IBillboardSceneNode* billboardNode;
	IMesh* billboardMesh;
};

