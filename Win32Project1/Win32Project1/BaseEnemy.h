#pragma once
#include "BaseObject2D.h"
class BaseEnemy :
	public BaseObject2D
{
public:
	BaseEnemy(const TCHAR * FileName, mEnemyBullet* obj, PlayerObject* PlayerObjectInstance);
	BaseEnemy(const TCHAR * FileName, mEnemyBullet* obj, PlayerObject* PlayerObjectInstance, double _X, double _Y);
	~BaseEnemy();
	double GetAngleToPlayer();

	int Count = 0;
	mEnemyBullet* mEnemyBulletObject;
	PlayerObject* PlayerObjectInstance;

	int mEnemyObjectLevel;
	int Level;
	int Pattern;
};

