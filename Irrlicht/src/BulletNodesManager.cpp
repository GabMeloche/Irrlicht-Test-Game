#include <BulletNodesManager.h>
#include <Bullet.h>



BulletNodesManager::BulletNodesManager()
{
	bulletsShot = 0;
}


BulletNodesManager::~BulletNodesManager()
{
}

void BulletNodesManager::createBullet(ISceneManager* smgr, IVideoDriver* driver)
{
	ICameraSceneNode* camera = smgr->getActiveCamera();
	line3d<f32> ray;
	ray.start = camera->getPosition();
	ray.end = ray.start + (camera->getTarget() - ray.start.normalize() * 1000.0f);
	vector3df direction = ray.getVector().normalize();

	IBillboardSceneNode* bulletBill = smgr->addBillboardSceneNode(nullptr,
		dimension2d<f32>(10.0f, 10.0f),
		camera->getAbsolutePosition());
	bulletBill->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR);
	bulletBill->setMaterialTexture(0, driver->getTexture("res/media/particle.bmp"));
	bulletBill->setMaterialFlag(video::EMF_LIGHTING, false);
	bulletBill->setMaterialFlag(video::EMF_ZBUFFER, true);
	//bulletBill->setID(ID_IsNotPickable);

	this->addBullet(bulletBill, direction);
	//std::cout << direction.X << ", " << direction.Y << ", " << direction.Z << std::endl;
	//system("pause");
}

void BulletNodesManager::addBullet(IBillboardSceneNode* bullet, vector3df& vec)
{
	if (bullet == nullptr)
		return;
	
	++bulletsShot;
	Bullet newBullet(1.0f, 10, vec, bullet);
	bullets.emplace_back(newBullet);
}

void BulletNodesManager::removeBullet(IBillboardSceneNode* bullet)
{
	if (bullet == nullptr)
		return;

	--bulletsShot;

	for (unsigned int i = 0; i < bulletsShot; ++i)
	{
		if (bullets[i].getNode() == bullet)
			bullets.erase(bullets.begin() + i);
	}
}

int BulletNodesManager::getBulletsShot()
{
	return bulletsShot;
}

Bullet& BulletNodesManager::operator[](unsigned int i)
{
	return bullets[i];
}