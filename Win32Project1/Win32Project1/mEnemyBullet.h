#pragma once
class mEnemyBullet : public BaseObject
{
public:
	mEnemyBullet();
	void MyUpdate();
	void MyDraw();
	~mEnemyBullet();
	void MyPeculiarAction(BaseObject * obj);
};

