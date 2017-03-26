#pragma once
#include "BaseEnemy.h"
class Enemy :
	public BaseEnemy
{
public:
	Enemy(const TCHAR * FileName, mEnemyBullet* obj, PlayerObject* PlayerObjectInstance);
	Enemy(const TCHAR * FileName, mEnemyBullet* obj, PlayerObject* PlayerObjectInstance, double _X, double _Y);

	void MyUpdate();
	void MyDraw();
	void MyPeculiarAction(BaseObject* obj);
	~Enemy();
};