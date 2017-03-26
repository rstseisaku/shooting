#pragma once
#include "BulletPattern.h"

class mEnemyBullet : public BaseObject
{
public:
	mEnemyBullet();
	void MyUpdate();
	void MyDraw();
	void MakeBullet(BulletPattern * BulletPatternObj);
	void AddBullet(BaseObject * obj);
	~mEnemyBullet();
	void MyPeculiarAction(BaseObject * obj);
	int ColEllipsPoint(double PlayerX, double PlayerY, BaseObject2D * Elp);

	// 弾幕に与えるスコア	
	int SetGrazeScore = 1; // グレイズスコア。得点アイテム取得数から算出。
	int SetEraseScore = 1; // ボムスコア。レベルから算出。
};

