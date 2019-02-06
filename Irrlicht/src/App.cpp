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
/*
In the Irrlicht Engine, everything can be found in the namespace 'irr'. So if
you want to use a class of the engine, you have to write irr:: before the name
of the class. For example to use the IrrlichtDevice write: irr::IrrlichtDevice.
To get rid of the irr:: in front of the name of every class, we tell the
compiler that we use that namespace from now on, and we will not have to write
irr:: anymore.
*/
using namespace irr;

/*
There are 5 sub namespaces in the Irrlicht Engine. Take a look at them, you can
read a detailed description of them in the documentation by clicking on the top
menu item 'Namespace List' or by using this link:
http://irrlicht.sourceforge.net/docu/namespaces.html
Like the irr namespace, we do not want these 5 sub namespaces now, to keep this
example simple. Hence, we tell the compiler again that we do not want always to
write their names.
*/
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

/*
To be able to use the Irrlicht.DLL file, we need to link with the Irrlicht.lib.
We could set this option in the project settings, but to make it easy, we use a
pragma comment lib for VisualStudio. On Windows platforms, we have to get rid
of the console window, which pops up when starting a program with main(). This
is done by the second pragma. We could also use the WinMain method, though
losing platform independence then.
*/
/*#ifdef _IRR_WINDOWS_
#pragma comment(lib, "Irrlicht.lib")
#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif*/

/*
This is the main method. We can now use main() on every platform.
*/

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

int main()
{
	EventReceiver receiver;
	Player player;
	BulletNodesManager bulletsManager;
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

	// future UI
	guienv->addStaticText(L"Hello World! This is the Irrlicht Software renderer!",
		rect<s32>(10, 10, 260, 22), true);

	IAnimatedMesh* sydneyMesh = smgr->getMesh("res/media/sydney.md2");

	if (!sydneyMesh)
	{
		device->drop();
		return 1;
	}

	IAnimatedMeshSceneNode* sydneyNode = smgr->addAnimatedMeshSceneNode(sydneyMesh);

	if (sydneyNode)
	{
		sydneyNode->setPosition(core::vector3df(-90, -25, 20));
		sydneyNode->setScale(core::vector3df(1.5f));
		scene::ITriangleSelector* selector = smgr->createTriangleSelector(sydneyNode);
		sydneyNode->setMaterialFlag(EMF_LIGHTING, false);
		sydneyNode->setMD2Animation(scene::EMAT_STAND);
		sydneyNode->setMaterialTexture(0, driver->getTexture("res/media/sydney.bmp"));
		
		/* This part should make Sydney collidable, but doesn't really work yet
		scene::ISceneNodeAnimator* anim = smgr->createCollisionResponseAnimator(
			selector, sydneyNode, core::vector3df(30, 50, 30),
			core::vector3df(0, -10, 0), core::vector3df(0, 30, 0));
		selector->drop(); // As soon as we're done with the selector, drop it.
		sydneyNode->addAnimator(anim);*/
	}

	device->getCursorControl()->setVisible(false);

	//FPS HANDLER
	int lastFPS = -1;
	// In order to do framerate independent movement, we have to know
	// how long it was since the last frame
	u32 then = device->getTimer()->getTime();

	// This is the movemen speed in units per second.
	const f32 MOVEMENT_SPEED = 5.f;

	while (device->run())
	{
		ICameraSceneNode* camera = smgr->getActiveCamera();

		if (device->isWindowActive())
		{
			const u32 now = device->getTimer()->getTime();
			const f32 frameDeltaTime = (f32)(now - then) / 1000.f; // Time in seconds
//<<<<<<< HEAD
			then = now;

			if (receiver.IsKeyDown(irr::KEY_ESCAPE))
				break;

			if (receiver.IsMouseDown(0))
			{
				bulletsManager.createBullet(smgr, driver);
			}

			//make bullets move
			for (int i = 0; i < bulletsManager.getBulletsShot(); ++i)
			{
				vector3df newPos = bulletsManager[i].getNode()->getPosition();
				bulletsManager[i].getNode()->setPosition(bulletsManager[i].getVec() + newPos);
			}

			driver->beginScene(true, true, SColor(255, 100, 101, 140));

			smgr->drawAll();
			guienv->drawAll();

			&CGUIBar::renderGUIBars;
			driver->endScene();
/*=======
			then = now;

			if (receiver.IsKeyDown(irr::KEY_ESCAPE))
				break;

			driver->beginScene(true, true, SColor(255, 100, 101, 140));

			smgr->drawAll();
			guienv->drawAll();
			
			&CGUIBar::renderGUIBars;
			
			driver->endScene();

>>>>>>> b03025b9a3e0310a241e3b9a035c211083254e08*/
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

	/*
	After we are done with the render loop, we have to delete the Irrlicht
	Device created before with createDevice(). In the Irrlicht Engine, you
	have to delete all objects you created with a method or function which
	starts with 'create'. The object is simply deleted by calling ->drop().
	See the documentation at irr::IReferenceCounted::drop() for more
	information.
	*/
	device->drop();
	return 0;
}

/*
That's it. Compile and run.
**/
