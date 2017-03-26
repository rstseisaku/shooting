#include "stdafx.h"
#include "Enemy.h"


Enemy::Enemy(const TCHAR * FileName, mEnemyBullet* obj, PlayerObject* obj2)
	: BaseEnemy(FileName, obj, obj2) {}

Enemy::Enemy(const TCHAR * FileName, mEnemyBullet * obj, PlayerObject* obj2, double _X, double _Y)
	: BaseEnemy(FileName, obj, obj2, _X, _Y) {}

void Enemy::MyUpdate()
{
	// グレイズ時・ボム時に加算するスコアを、弾管理オブジェクトに格納 
	mEnemyBulletObject->SetGrazeScore = Level * 10 + 
		PlayerObjectInstance->GetItemNum + PlayerObjectInstance->GetRareItemNum * 3;
	mEnemyBulletObject->SetEraseScore = mEnemyBulletObject->SetGrazeScore / 2;

	if (Pattern == NOSELECTED) {
		Pattern = GetRand( PatternNum - 1 ) + 1 ; // NOSELECTEDを選ばない様に
		Count = 0;
		val1 = 0;
		Level = mEnemyObjectLevel;

		// Pattern = GURUGURU2;
	}
	else if ( Pattern == GURUGURU ) {
		MyUpdateGuruguru();
	}
	else if (Pattern == KOUSA) {
		MyUpdateKousa();
	}
	else if (Pattern == JIKINERAI) {
		MyUpdateJikinerai();
	}
	else if (Pattern == IYAGARASE) {
		MyUpdateIyagarase();
	}
	else if (Pattern == JIYUURAKKA) {
		MyUpdateJiyurakka();
	}
	else if (Pattern == GURUGURU2) {
		MyUpdateGuruguru2();
	}
}

void Enemy::MyDraw() 
{
	// 画像の描画
	DrawGraph((int)GetDrawX(), (int)GetDrawY(), GraphicHandle, true);
}

void Enemy::MyPeculiarAction(BaseObject* obj) 
{
	// 特に何もない
}

Enemy::~Enemy()
{
}



/*
 * 以下に弾幕パターンを書く
 */
void Enemy::MyUpdateGuruguru() {
	Count++;
	if (Count == 900) Pattern = NOSELECTED;
	if (Count == 99 || Count == 299) {
		BulletPattern *bp = new BulletPattern();
		bp->X = CenterX;
		bp->Y = CenterY;
		bp->FileName = _T("Image/bullet5_white.png");
		bp->Angle = GetAngleToPlayer();

		bp->CompositeModeParameter = ADD;
		bp->Transparency = 200;
		bp->vAngle = 8;
		bp->Speed = 70.0;
		bp->N = (Level + 1) * 2;
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
		Level = mEnemyObjectLevel;

		BulletPattern *bp = new BulletPattern();
		bp->X = CenterX;
		bp->Y = CenterY;
		bp->FileName = _T("Image/bullet5_white.png");
		bp->CompositeModeParameter = ADD;
		bp->Angle = GetAngleToPlayer();
		bp->Transparency = 200;
		bp->vAngle = -8;
		bp->Speed = 70.0;
		bp->N = (Level + 1) * 2;
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
}

void Enemy::MyUpdateJikinerai() {
	Count++;
	if (Count == 510) Pattern = NOSELECTED;

	int frequency = 30;
	frequency -= Level * 2;
	if (frequency < 10) frequency = 10;
	if (Count >= 90 && Count <= 450 && Count % frequency == 0) {
		BulletPattern *bp = new BulletPattern(  );
		bp->X = CenterX;
		bp->Y = CenterY;
		bp->FileName = _T("Image/bullet5_orange.png");
		bp->CompositeModeParameter = ADD;
		bp->Transparency = 200;
		bp->Speed = 250.0 + 10 * Level;
		bp->Angle = GetAngleToPlayer();
		bp->N = (Level * 2) + 1;
		if (bp->N >= 11) bp->N = 11;
		bp->Span = (80.0 + Level * 18) / bp->N;
		mEnemyBulletObject->MakeBullet(bp);
	}
}

void Enemy::MyUpdateKousa() {
	Count++;
	if (Count == 600) Pattern = NOSELECTED;

	if (Count == 90) {
		BulletPattern *bp = new BulletPattern();
		bp->X = CenterX;
		bp->Y = CenterY;
		bp->N = (Level + 1) * 4;
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
}

void Enemy::MyUpdateIyagarase() {
	Count++;
	if (Count == 600) Pattern = NOSELECTED;

	int frequency = 40;
	frequency -= Level * 2;
	if (frequency < 10) frequency = 20;
	if (Count >= 90 && Count <= 400 && Count % frequency == 0) {
		BulletPattern *bp = new BulletPattern();
		bp->X = CenterX;
		bp->Y = CenterY;
		bp->Angle = GetAngleToPlayer();
		bp->CompositeModeParameter = ADD;
		bp->Transparency = 200;
		bp->vAngle = 0.6 + Level*0.15;

		bp->FileName = _T("Image/bullet5_orange.png");
		bp->Speed = 160.0 - 7 * Level;
		if (bp->Speed <= 100) bp->Speed = 100;
		bp->N = 4 + Level * 2;
		if (bp->N >= 12) bp->N = 12;
		bp->Span = 180 / bp->N;
		mEnemyBulletObject->MakeBullet(bp);

		bp->FileName = _T("Image/bullet5_white.png");
		bp->Speed = 210.0 + 7 * Level;
		if (bp->Speed >= 320) bp->Speed = 320;
		bp->N = 5 + Level * 2;
		if (bp->N >= 12) bp->N = 13;
		bp->Span = 180 / bp->N;
		mEnemyBulletObject->MakeBullet(bp);
	}
}

void Enemy::MyUpdateJiyurakka() {
	Count++;
	if (Count == 600) Pattern = NOSELECTED;

	if ( Count == 30 || Count == 60 || Count == 90 || Count == 120 ) {
		if (Level <= 2 && Count == 90) return;
		if (Level <= 3 && Count == 120) return;

		int Way = 20 + Level * 4;
		if (Way >= 56) Way = 56;
		double vx, vy, vvx, vvy;
		vvx = 0;
		for (int i = 0; i < Way; i++) {
			vx = GetRand(10)*0.4 - 2.00;
			vy = GetRand(10)*0.1 - 5.5;
			vvy = GetRand(10)*0.01 + 0.04;
			Bullet* tmp = new Bullet(
				_T("Image/bullet4_blue.png"),
				CenterX, CenterY,
				vx, vy, vvx, vvy);
			mEnemyBulletObject->AddBullet(tmp);
		}
	}
}

void Enemy::MyUpdateGuruguru2() {
	Count++;
	if (Count == 600) Pattern = NOSELECTED;
	
	int tmp = 7 - Level;
	if ( tmp <= 4) tmp = 4;
	int tmp2 = Count % tmp;
	if ( tmp2 == 0 && Count <= 360 && Count >= 60) {
		if (Level <= 2) { Angle += val1; }
		val1 += 1.6;

		BulletPattern *bp = new BulletPattern();
		bp->FileName = _T("Image/bullet6_white.png");
		bp->Speed = 160.0 + Level * 10;
		bp->Angle = Angle;
		if (bp->Speed >= 320) bp->Speed = 320;
		bp->N = 7 + Level;
		if (bp->N >= 25) bp->N = 25;
		bp->Span = 360 / bp->N;
		mEnemyBulletObject->MakeBullet(bp);
	}
}
