#pragma once
#include "BulletPattern.h"

class mEnemyBullet : public BaseObject
{
public:
	mEnemyBullet();
	void MyUpdate();
	void MyDraw();
	void MakeBullet(BulletPattern * BulletPatternObj);
	~mEnemyBullet();
	void MyPeculiarAction(BaseObject * obj);
	bool ColEllipsPoint(double PlayerX, double PlayerY, BaseObject2D * Elp);
};

