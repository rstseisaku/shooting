#pragma once
#include "BaseObject2D.h"
class Enemy :
	public BaseObject2D
{
public:
	Enemy(const TCHAR * FileName, mEnemyBullet* obj, PlayerObject* PlayerObjectInstance);
	Enemy(const TCHAR * FileName, mEnemyBullet* obj, PlayerObject* PlayerObjectInstance, double _X, double _Y);

	void MyUpdate();
	void MyDraw();
	void MyPeculiarAction(BaseObject* obj);
	~Enemy();

	double GetAngleToPlayer();


	int Count = 0;
	mEnemyBullet* mEnemyBulletObject;
	PlayerObject* PlayerObjectInstance;
};