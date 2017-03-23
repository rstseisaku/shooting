#pragma once
class mEnemyBullet : public BaseObject
{
public:
	mEnemyBullet();
	void MyUpdate();
	void MyDraw();
	~mEnemyBullet();
	void MyPeculiarAction(BaseObject * obj);
	bool ColEllipsPoint(double PlayerX, double PlayerY, BaseObject2D * Elp);
};

