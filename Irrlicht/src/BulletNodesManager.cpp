#include <BulletNodesManager.h>
#include <Bullet.h>

BulletNodesManager::BulletNodesManager()
{
	bulletsShot = 0;
}

BulletNodesManager::~BulletNodesManager()
{
	if (smgr)
		smgr->drop();
}

void BulletNodesManager::createBullet(ISceneManager* smgr, IVideoDriver* driver)
{
	//calculate player camera direction vector
	ICameraSceneNode* camera = smgr->getActiveCamera();

	IBillboardSceneNode* bulletBill = smgr->addBillboardSceneNode(nullptr,
		dimension2d<f32>(10.0f, 10.0f),
		camera->getAbsolutePosition());
	bulletBill->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR);
	bulletBill->setMaterialTexture(0, driver->getTexture("res/media/particle.bmp"));
	bulletBill->setMaterialFlag(video::EMF_LIGHTING, false);
	bulletBill->setMaterialFlag(video::EMF_ZBUFFER, true);

	this->addBullet(bulletBill);
}

void BulletNodesManager::addBullet(IBillboardSceneNode* bullet)
{
	if (bullet == nullptr)
		return;
	
	line3d<f32> ray = smgr->getSceneCollisionManager()->getRayFromScreenCoordinates(position2d<s32>(400, 300));
	bullets.emplace_back(Bullet (10, 1.0f, ray, bullet));
	ITriangleSelector* triangleSelector = smgr->createTriangleSelectorFromBoundingBox(bullet);
	bullet->setTriangleSelector(triangleSelector);
	triangleSelector->drop();
	++bulletsShot;
}

void BulletNodesManager::removeBullet(int index)
{

	for (unsigned int i = 0; i < bulletsShot; ++i)
	{
		if (bullets[i].getNode() == bullets[index].getNode())
		{
			bullets[index].getNode()->remove();
			bullets.erase(bullets.begin() + i);
			--bulletsShot;
		}
	}
}

void BulletNodesManager::moveBullets(ISceneManager* smgr)
{
	ISceneCollisionManager* collMan = smgr->getSceneCollisionManager();

	for (int i = 0; i < getBulletsShot(); ++i)
	{
		vector3df tmpPoint;
		triangle3df tmpTriangle;
		ISceneNode* node;

		vector3df newPos = bullets[i].getNode()->getPosition();
		bullets[i].getNode()->setPosition(
			(bullets[i].getVec() + newPos) * bullets[i].getSpeed());

		bullets[i].addDistance();
	}
}

int BulletNodesManager::getBulletsShot()
{
	return bulletsShot;
}

void BulletNodesManager::setSmgr(ISceneManager* p_smgr)
{
	smgr = p_smgr;
}

Bullet& BulletNodesManager::operator[](unsigned int i)
{
	return bullets[i];
}