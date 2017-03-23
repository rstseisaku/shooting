#include "stdafx.h"
#include "Enemy.h"


Enemy::Enemy(const TCHAR * FileName, mEnemyBullet* obj)
{
	InitCommon(FileName);
	mEnemyBulletObject = obj;
}

Enemy::Enemy(const TCHAR * FileName, mEnemyBullet * obj, double _X, double _Y)
{
	InitCommon(FileName);
	mEnemyBulletObject = obj;
	CenterX = _X;
	CenterY = _Y;
}

void Enemy::MyUpdate()
{
	Count++;
	Count %= 450;
	if (Count == 149) {
		BulletPattern *bp = new BulletPattern();
		bp->FileName = _T("Image/bullet5.png");
		bp->CompositeModeParameter = ADD;
		bp->Transparency = 200;
		bp->vAngle = 8;
		bp->Speed = 70.0;
		bp->N = 12;
		bp->Span = 360.0 / bp->N;
		mEnemyBulletObject->MakeBullet(bp);

		bp->Speed = 120.0;
		bp->Angle += bp->Span / 3;
		mEnemyBulletObject->MakeBullet(bp);

		bp->Speed = 170.0;
		bp->Angle += bp->Span / 3;
		mEnemyBulletObject->MakeBullet(bp);

		bp->Speed = 240.0;
		bp->Angle += bp->Span / 3;
		mEnemyBulletObject->MakeBullet(bp);
	}
	if (Count == 299) {
		BulletPattern *bp = new BulletPattern();
		bp->FileName = _T("Image/bullet5.png");
		bp->CompositeModeParameter = ADD;
		bp->Transparency = 200;
		bp->vAngle = -8;
		bp->Speed = 70.0;
		bp->N = 12;
		bp->Span = 360.0 / bp->N;
		mEnemyBulletObject->MakeBullet(bp);

		bp->Speed = 120.0;
		bp->Angle += bp->Span / 3;
		mEnemyBulletObject->MakeBullet(bp);

		bp->Speed = 170.0;
		bp->Angle += bp->Span / 3;
		mEnemyBulletObject->MakeBullet(bp);

		bp->Speed = 240.0;
		bp->Angle += bp->Span / 3;
		mEnemyBulletObject->MakeBullet(bp);
	}
	if (Count == 449) {
		BulletPattern *bp = new BulletPattern();
		bp->N = 20;
		bp->Span = 360.0 / bp->N;
		bp->CompositeModeParameter = NORMAL;
		bp->FileName = _T("Image/bullet4.png");
		bp->Speed = 50.0;

		bp->vAngle = 4;
		mEnemyBulletObject->MakeBullet(bp);
		bp->vAngle = -4;
		mEnemyBulletObject->MakeBullet(bp);
	}
}

void Enemy::MyDraw() 
{
	// ‰æ‘œ‚Ì•`‰æ
	DrawGraph((int)GetDrawX(), (int)GetDrawY(), GraphicHandle, true);
}

void Enemy::MyPeculiarAction(BaseObject* obj) 
{
	// “Á‚É‰½‚à‚È‚¢
}

Enemy::~Enemy()
{
}
