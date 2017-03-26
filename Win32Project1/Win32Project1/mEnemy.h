#pragma once
#include "BaseObject.h"
class mEnemy :
	public BaseObject
{
public:
	mEnemy(BaseObject * _mEnemyBulletObject, BaseObject * _PlayerObject);
	~mEnemy();

	void MyUpdate();

	void MyDraw();

	void MyPeculiarAction(BaseObject * PlayerObj);

	BaseObject* mEnemyBulletObject;
	BaseObject* PlayerObjectInstance;

	int Level;
	int Counter;
};

