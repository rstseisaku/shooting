#include "stdafx.h"
#include "Enemy2.h"


/*
* BaseEnemy ���p�������G�N���X�T���v���B
  ( �Q�[�����ł͗��p���Ă��܂��� )
*/


Enemy2::Enemy2(const TCHAR * FileName, mEnemyBullet* obj, PlayerObject* obj2)
	: BaseEnemy(FileName, obj, obj2) {}

Enemy2::Enemy2(const TCHAR * FileName, mEnemyBullet * obj, PlayerObject* obj2, double _X, double _Y)
	: BaseEnemy(FileName, obj, obj2, _X, _Y) {}

void Enemy2::MyUpdate()
{
	Count++;
	Count %= 4000;
	if (Count == 10 ) {
		BulletPattern *bp = new BulletPattern();
		bp->X = CenterX;
		bp->Y = CenterY;
		bp->FileName = _T("Image/bullet5_orange.png");
		bp->CompositeModeParameter = NORMAL;
		bp->Transparency = 255;
		bp->Speed = 250.0;
		bp->Angle = GetAngleToPlayer();
		bp->Angle = 120;
		bp->N = 1;
		bp->Span = 180.0 / bp->N;
		mEnemyBulletObject->MakeBullet(bp);
	}
}

void Enemy2::MyDraw()
{
	// �摜�̕`��
	DrawGraph((int)GetDrawX(), (int)GetDrawY(), GraphicHandle, true);
}

void Enemy2::MyPeculiarAction(BaseObject* obj)
{
	// ���ɉ����Ȃ�
}

Enemy2::~Enemy2()
{
	MyDestructor();
}