#pragma once
#include <irrlicht.h>


class CCrossHair : public irr::gui::IGUIElement
{
public:
	CCrossHair(irr::gui::IGUIEnvironment *  environment, irr::u32 id = -1) : irr::gui::IGUIElement(irr::gui::EGUIET_ELEMENT, environment, environment->getRootGUIElement(), id, irr::core::rect< irr::s32 >(0, 0, 0, 0))
	{
		Texture = 0;
		Color = irr::video::SColor(255, 255, 255, 0);
		Size = 10;
	}

	virtual ~CCrossHair(void)
	{
		if (Texture)
			Texture->drop();
	}

	void draw(void)
	{
		irr::video::IVideoDriver* driver = Environment->getVideoDriver();

		irr::u32 screenW = driver->getScreenSize().Width;
		irr::u32 screenH = driver->getScreenSize().Height;
		irr::u32 cenW = screenW / 2;
		irr::u32 cenH = screenH / 2;

		if (!Texture)
		{
			//Draw crosshair
			driver->draw2DRectangle(Color, irr::core::rect<irr::s32>(cenW - 1, cenH - Size, cenW + 1, cenH - 4)); //above
			driver->draw2DRectangle(Color, irr::core::rect<irr::s32>(cenW + 4, cenH - 1, cenW + Size, cenH + 1)); //right
			driver->draw2DRectangle(Color, irr::core::rect<irr::s32>(cenW - 1, cenH + 4, cenW + 1, cenH + Size)); //down
			driver->draw2DRectangle(Color, irr::core::rect<irr::s32>(cenW - Size, cenH - 1, cenW - 4, cenH + 1)); //left
			driver->draw2DRectangle(Color, irr::core::rect<irr::s32>(cenW - 1, cenH - 1, cenW + 1, cenH + 1)); //center of screen
		}
		else
		{
			irr::video::SColor Colors[] = { Color, Color, Color, Color };
			driver->draw2DImage(Texture, irr::core::rect< irr::s32 >(cenW - Size, cenH - Size, cenW + Size, cenH + Size), irr::core::rect< irr::s32 >(0, 0, Texture->getOriginalSize().Width, Texture->getOriginalSize().Height), 0, Colors, true);
		}

	}

	void setTexture(irr::video::ITexture* texture)
	{
		if (Texture)
			Texture->drop();

		Texture = texture;

		if (Texture)
			Texture->grab();
	}

	void setSize(irr::u32 size)
	{
		Size = size;
	}

	void setColor(irr::video::SColor color)
	{
		Color = color;
	}
protected:
	irr::video::ITexture* Texture;
	irr::u32 Size;
	irr::video::SColor Color;
};