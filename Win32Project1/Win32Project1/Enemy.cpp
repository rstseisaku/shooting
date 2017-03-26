#include "stdafx.h"
#include "Enemy.h"


Enemy::Enemy(const TCHAR * FileName, mEnemyBullet* obj, PlayerObject* obj2)
{
	InitCommon(FileName);
	mEnemyBulletObject = obj;
	PlayerObjectInstance = obj2;
}

Enemy::Enemy(const TCHAR * FileName, mEnemyBullet * obj, PlayerObject* obj2, double _X, double _Y)
{
	InitCommon(FileName);
	mEnemyBulletObject = obj;
	CenterX = _X;
	CenterY = _Y;
	PlayerObjectInstance = obj2;
}

void Enemy::MyUpdate()
{
	Count++;
	Count %= 1300;
	if ( Count == 99 || Count == 299 ) {
		BulletPattern *bp = new BulletPattern();
		bp->X = CenterX;
		bp->Y = CenterY;
		bp->FileName = _T("Image/bullet5_white.png");
		bp->Angle = GetAngleToPlayer();

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

		bp->Speed = 310.0;
		bp->Angle += bp->Span / 3;
		mEnemyBulletObject->MakeBullet(bp);
	}
	if (Count == 199 || Count == 399) {
		BulletPattern *bp = new BulletPattern();
		bp->X = CenterX;
		bp->Y = CenterY;
		bp->FileName = _T("Image/bullet5_white.png");
		bp->CompositeModeParameter = ADD;
		bp->Angle = GetAngleToPlayer();
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

		bp->Speed = 310.0;
		bp->Angle += bp->Span / 3;
		mEnemyBulletObject->MakeBullet(bp);
	}
	if (Count == 699) {
		BulletPattern *bp = new BulletPattern();
		bp->X = CenterX;
		bp->Y = CenterY;
		bp->N = 20;
		bp->Span = 360.0 / bp->N;
		bp->CompositeModeParameter = NORMAL;
		bp->Angle = GetAngleToPlayer();

		bp->FileName = _T("Image/bullet4_blue.png");
		bp->Speed = 65.0;
		bp->vAngle = 6;
		mEnemyBulletObject->MakeBullet(bp);
		bp->vAngle = -6;
		mEnemyBulletObject->MakeBullet(bp);

		bp->FileName = _T("Image/bullet4_yellow.png");
		bp->Speed = 100.0;
		bp->vAngle = 8;
		mEnemyBulletObject->MakeBullet(bp);
		bp->vAngle = -8;
		mEnemyBulletObject->MakeBullet(bp);

		bp->FileName = _T("Image/bullet4_red.png");
		bp->Speed = 160.0;
		bp->vAngle = 12;
		mEnemyBulletObject->MakeBullet(bp);
		bp->vAngle = -12;
		mEnemyBulletObject->MakeBullet(bp);
	}
	if (Count % 7 == 0 && Count >= 1100 && Count <= 1300) {
		BulletPattern *bp = new BulletPattern();
		bp->X = CenterX;
		bp->Y = CenterY;
		bp->FileName = _T("Image/bullet5_orange.png");
		bp->CompositeModeParameter = ADD;
		bp->Transparency = 200;
		bp->Speed = 200.0 + ( Count - 1100 ) * 3;
		bp->Angle = GetAngleToPlayer();
		bp->N = 5;
		bp->Span = 70.0 / bp->N;
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


double Enemy::GetAngleToPlayer() {
	// ©‹@‚Ö‚ÌŠp“x‚ğ‹‚ß‚é
	double Ans = 
		atan2(PlayerObjectInstance->CenterY - CenterY,
			PlayerObjectInstance->CenterX - CenterX);
	Ans = Ans * 180.0 / M_PI; // “x = ƒ‰ƒWƒAƒ“ ~ 180 € ‰~ü—¦
	return Ans;
}