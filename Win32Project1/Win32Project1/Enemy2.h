#pragma once
#include "BaseEnemy.h"
class Enemy2 :
	public BaseEnemy
{
public:
public:
	Enemy2(const TCHAR * FileName, mEnemyBullet* obj, PlayerObject* PlayerObjectInstance);
	Enemy2(const TCHAR * FileName, mEnemyBullet* obj, PlayerObject* PlayerObjectInstance, double _X, double _Y);

	void MyUpdate();
	void MyDraw();
	void MyPeculiarAction(BaseObject* obj);
	~Enemy2();
};

