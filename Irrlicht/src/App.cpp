/** Example 001 HelloWorld

This Tutorial shows how to set up the IDE for using the Irrlicht Engine and how
to write a simple HelloWorld program with it. The program will show how to use
the basics of the VideoDriver, the GUIEnvironment, and the SceneManager.
Microsoft Visual Studio is used as an IDE, but you will also be able to
understand everything if you are using a different one or even another
operating system than windows.

You have to include the header file <irrlicht.h> in order to use the engine. The
header file can be found in the Irrlicht Engine SDK directory \c include. To let
the compiler find this header file, the directory where it is located has to be
specified. This is different for every IDE and compiler you use. Let's explain
shortly how to do this in Microsoft Visual Studio:

- If you use Version 6.0, select the Menu Extras -> Options.
Select the directories tab, and select the 'Include' Item in the combo box.
Add the \c include directory of the irrlicht engine folder to the list of
directories. Now the compiler will find the Irrlicht.h header file. We also
need the irrlicht.lib to be found, so stay in that dialog, select 'Libraries'
in the combo box and add the \c lib/VisualStudio directory.
\image html "vc6optionsdir.jpg"
\image latex "vc6optionsdir.jpg"
\image html "vc6include.jpg"
\image latex "vc6include.jpg"

- If your IDE is Visual Studio .NET, select Tools -> Options.
Select the projects entry and then select VC++ directories. Select 'show
directories for include files' in the combo box, and add the \c include
directory of the irrlicht engine folder to the list of directories. Now the
compiler will find the Irrlicht.h header file. We also need the irrlicht.lib
to be found, so stay in that dialog, select 'show directories for Library
files' and add the \c lib/VisualStudio directory.
\image html "vcnetinclude.jpg"
\image latex "vcnetinclude.jpg"

That's it. With your IDE set up like this, you will now be able to develop
applications with the Irrlicht Engine.

Lets start!

After we have set up the IDE, the compiler will know where to find the Irrlicht
Engine header files so we can include it now in our code.
*/
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

/*void Init()
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
	IGUIEnvironment* guienv = device->getGUIEnvironment();
	CGUIBar healthBar(30, 540, 200, 570, 100, 0, "Health");

	BulletNodesManager bulletsManager;
	bulletsManager.setSmgr(smgr);

	Player player;
	Enemy enemy(smgr, driver);

	device->getCursorControl()->setVisible(false);
}*/

void Run()
{

}

int main()
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
	// This is the movemen speed in units per second.
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

			//make bullets move
			for (int i = 0; i < bulletsManager.getBulletsShot(); ++i)
			{
				vector3df tmpPoint;
				triangle3df tmpTriangle;
				ISceneNode* node;
				//bool collided = smgr->getSceneCollisionManager()->getCollisionPoint(
					//bulletsManager[i].getRay(), sydneyNode->getTriangleSelector(), tmpPoint, tmpTriangle, node);

				vector3df newPos = bulletsManager[i].getNode()->getPosition();
				bulletsManager[i].getNode()->setPosition( 
					(bulletsManager[i].getVec() + newPos) * bulletsManager[i].getSpeed());

				bulletsManager[i].addDistance();
				
				if (bulletsManager[i].getDistance() == 1000.0f)
				{
					bulletsManager.removeBullet(i);
				}
			}

			if (then % 2000 == 0)
			{

				if (player.getHealth() <= 0)
				{
					IGUIStaticText* text = guienv->addStaticText(L"You Lost!",
						rect<s32>(300, 260, 500, 300), true);
					text->setBackgroundColor(SColor());
					text->setTextAlignment(EGUIA_CENTER, EGUIA_CENTER);
					text->setOverrideColor(SColor(255, 255, 0, 0));
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
