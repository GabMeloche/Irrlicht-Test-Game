#include <irrlicht.h>
#include <EventReceiver.h>
#include <Scene.h>
#include <Player.h>
#include <iostream>
#include <Bullet.h>
#include <BulletNodesManager.h>
#include <UIGame.h>
#include <Enemy.h>
#include <CrossHair.h>
#include <string>

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

void drawText(IGUIEnvironment* guienv, Player& player)
{
	if (player.getHealth() <= 0)
	{
		IGUIStaticText* text = guienv->addStaticText(L"GAME OVER",
			rect<s32>(300, 260, 500, 300), true);
		text->setBackgroundColor(SColor());
		text->setTextAlignment(EGUIA_CENTER, EGUIA_CENTER);
		text->setOverrideColor(SColor(255, 255, 0, 0));

		std::string scoreString = "Score: " + std::to_string(player.getScore());
		std::wstring scoreWString = std::wstring(scoreString.begin(), scoreString.end());
		const wchar_t* score = scoreWString.c_str();

		IGUIStaticText* textScore = guienv->addStaticText(score,
			rect<s32>(300, 310, 500, 340), false);
		textScore->setBackgroundColor(SColor());
		textScore->setTextAlignment(EGUIA_CENTER, EGUIA_CENTER);
	}
	else
	{
		player.setHealth(player.getHealth() - 1);
		IGUIStaticText* text = guienv->addStaticText(L"Find and Shoot Sydney!",
			rect<s32>(300, 50, 500, 100), false);

		text->setTextAlignment(EGUIA_CENTER, EGUIA_CENTER);
		text->setOverrideColor(SColor(255, 255, 255, 255));
	}
}

int Run()
{
	EventReceiver receiver;
	IrrlichtDevice* device =
		createDevice(video::EDT_DIRECT3D9, dimension2d<u32>(800, 600), 16,
			false, false, false, &receiver);

	if (!device)
		return 1;

	device->setWindowCaption(L"Hello World! - Irrlicht Engine Demo");

	Scene scene(device);
	ISceneManager* smgr = scene.getSmgr();
	IVideoDriver* driver = device->getVideoDriver();
	ISceneCollisionManager* collMan = smgr->getSceneCollisionManager();
	IGUIEnvironment* guienv = device->getGUIEnvironment();
	CGUIBar healthBar(30, 540, 200, 570, 100, 0, "Health");
	CCrossHair crosshair(guienv);
	BulletNodesManager bulletsManager;
	bulletsManager.setSmgr(smgr);

	Player player;
	Enemy enemy(smgr, driver);

	device->getCursorControl()->setVisible(false);

	//FPS HANDLER
	int lastFPS = -1;
	u32 then = device->getTimer()->getTime();

	// This is the movement speed in units per second.
	const f32 MOVEMENT_SPEED = 5.f;

	while (device->run())
	{
		ICameraSceneNode* camera = smgr->getActiveCamera();
		if (device->isWindowActive())
		{
			healthBar.setBarValue(player.getHealth());
			const u32 now = device->getTimer()->getTime();
			const f32 frameDeltaTime = (f32)(now - then) / 1000.f; // Time in seconds
			then = now;

			if (receiver.IsKeyDown(irr::KEY_ESCAPE))
				break;

			if (receiver.IsMouseDown(0) && then % 20 == 0)
			{
				bulletsManager.createBullet(smgr, driver);
			}

			//make all bullets move
			bulletsManager.moveBullets(smgr);

			for (int i = 0; i < bulletsManager.getBulletsShot(); ++i)
			{
				//Collisions check
				core::vector3df intersection;
				core::triangle3df hitTriangle;

				scene::ISceneNode * selectedSceneNode =
					collMan->getSceneNodeAndCollisionPointFromRay(
						bulletsManager[i].getRay(),
						intersection,
						hitTriangle, 
						IDFlag_IsPickable,				   
						0);

				if (selectedSceneNode == enemy.getNode())
				{
					enemy.setRandomPos();
					selectedSceneNode = 0;
					player.setScore(player.getScore() + 1);
					//std::cout << "score: " << player.getScore() << std::endl;			
				}

				if (bulletsManager[i].getDistance() == 1000.0f)
				{
					bulletsManager.removeBullet(i);
				}
			}

			if (then % 500 == 0)
			{
				drawText(guienv, player);
			}

			driver->beginScene(true, true, SColor(255, 100, 101, 140));
			crosshair.draw();
			smgr->drawAll();
			guienv->drawAll();
			healthBar.renderGUIBars(driver);
			driver->endScene();

			int fps = driver->getFPS();

			if (lastFPS != fps)
			{
				core::stringw tmp(L"Quake Remake - Irrlicht Engine [");
				tmp += driver->getName();
				tmp += L"] fps: ";
				tmp += fps;

				device->setWindowCaption(tmp.c_str());
				lastFPS = fps;
			}
		}
		else
			device->yield();
	}

	device->drop();
	return 0;
}


int main()
{
	return Run();
}
