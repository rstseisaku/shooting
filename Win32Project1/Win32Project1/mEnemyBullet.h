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

	// �e���ɗ^����X�R�A	
	int SetGrazeScore = 1; // �O���C�Y�X�R�A�B���_�A�C�e���擾������Z�o�B
	int SetEraseScore = 1; // �{���X�R�A�B���x������Z�o�B
};

