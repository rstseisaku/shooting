#pragma once
#include "BaseObject2D.h"
class Enemy :
	public BaseObject2D
{
public:
	Enemy(const TCHAR * FileName, mEnemyBullet* obj);
	Enemy(const TCHAR * FileName, mEnemyBullet* obj, double _X, double _Y);

	void MyUpdate();
	void MyDraw();
	void MyPeculiarAction(BaseObject* obj);
	~Enemy();


	int Count = 0;
	mEnemyBullet* mEnemyBulletObject;
};