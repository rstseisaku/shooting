#pragma once
#include "BaseObject.h"
class mEnemy :
	public BaseObject
{
public:
	mEnemy();
	mEnemy(BaseObject * obj);
	~mEnemy();

	void MyUpdate();

	void MyDraw();

	void MyPeculiarAction(BaseObject * PlayerObj);

	BaseObject* mEnemyBulletObject;
};

