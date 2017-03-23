#include "stdafx.h"

mEnemyBullet::mEnemyBullet()
{
	Layer = Layer_EnemyBullet;

	/*
	AddObject(new Bullet(_T("Image/bullet1.png"), 300, 300, 3, 0));
	AddObject(new Bullet(_T("Image/bullet1.png"), 300, 300, -3, 0));
	AddObject(new Bullet(_T("Image/bullet1.png"), 300, 300, 3, 3));
	AddObject(new Bullet(_T("Image/bullet1.png"), 300, 300, 0, 0));
	*/

	// for (int i = 0; i < 10; i++) {
	// 	AddObject(new Bullet2(_T("Image/bullet2.png"), 200, 200, i * 36, 100));
	// }
	// AddObject(new Bullet2(_T("Image/bullet3.png"), 300, 300, 0, 0, (int)ADD, 127));
	// AddObject(new Bullet2(_T("Image/bullet3.png"), 400, 300, 0, 0, (int)ADD, 127));
	// AddObject(new Bullet2(_T("Image/bullet3.png"), 350, 350, 0, 0));
	/*
	bp->Speed = 60;
	MakeBullet(bp);
	bp->Speed = 90;
	MakeBullet(bp);
	bp->Speed = 120;
	MakeBullet(bp);
	*/

	BulletPattern *bp = new BulletPattern();
	bp->Speed = 140;
	bp->CompositeModeParameter = ADD;
	bp->Transparency = 255;
	bp->N = 12;
	bp->Span = 360.0 / bp->N;
	MakeBullet(bp);

	bp->CompositeModeParameter = NORMAL;
	bp->Speed = 210;
	bp->Transparency = 64;
	bp->Angle += bp->Span / 3;
	MakeBullet(bp);

	bp->CompositeModeParameter = SUB;
	bp->Speed = 70;
	bp->Transparency = 127;
	bp->Angle += bp->Span / 3;
	MakeBullet(bp);
}

void mEnemyBullet::MyUpdate()
{
	for (auto itr = ObjectList.begin(); itr != ObjectList.end(); ++itr) {
		if ((*itr)->ObjectDeleteFlag) continue;
		(*itr)->MyUpdate();
	}
}

void mEnemyBullet::MyPeculiarAction(BaseObject * PlayerObj) {
	// プレイヤーオブジェクトを受け取り、当たり判定の処理を行う
	double PlayerObjectCenterX = PlayerObj->CenterX;
	double PlayerObjectCenterY = PlayerObj->CenterY;

	for (auto itr = ObjectList.begin(); itr != ObjectList.end(); ++itr) {
		if ((*itr)->ObjectDeleteFlag) continue;

		if (ColEllipsPoint(PlayerObjectCenterX, PlayerObjectCenterY, (BaseObject2D*)(*itr))) {
			// 衝突
			(*itr)->ObjectDelete();
			// DrawFormatString(5, 5, GetColor(0, 255, 255), _T("HIT!")); // 文字を描画する

			// 当たったアブジェクト全てに対してHitを呼び出す(引数に対象イテレタ)も
			// 考えられる( Unityとかの仕組み )
			// 今回はプレイヤと敵弾に絞って処理を組む
		}
	}
}

void mEnemyBullet::MyDraw()
{
	for (auto itr = ObjectList.begin(); itr != ObjectList.end();  ) {
		if ((*itr)->ObjectDeleteFlag) {
			delete((*itr));
			itr = ObjectList.erase( itr ); // 要素を削除、次要素を受け取る
			continue;
		}
		(*itr)->MyDraw();
		itr++;
	}

	DrawFormatString(45, 45, GetColor(0, 255, 255), _T("弾数 %d"), ObjectList.size()); // 文字を描画する
}


void mEnemyBullet::MakeBullet( BulletPattern *BulletPatternObj ) 
{
	int Angle = BulletPatternObj->Angle - (BulletPatternObj->N - 1) * BulletPatternObj->Span;
	for (int i = 0; i < BulletPatternObj->N; i++) {
		Bullet2 *tmp = new Bullet2(
			BulletPatternObj->FileName,
			BulletPatternObj->X,
			BulletPatternObj->Y,
			Angle,
			BulletPatternObj->Speed,
			BulletPatternObj->CompositeModeParameter,
			BulletPatternObj->Transparency);
		tmp->vAngle = 1;
		AddObject(tmp);
		Angle += BulletPatternObj->Span;
	}
}

mEnemyBullet::~mEnemyBullet()
{
}

bool mEnemyBullet::ColEllipsPoint(double PlayerX, double PlayerY, BaseObject2D* Elp)
{
	double ElpSizeX = Elp->WidthX * 0.4;
	double ElpSizeY = Elp->HeightY * 0.4;

	// 点に楕円→真円変換行列を適用
	double Ofs_x = PlayerX - Elp->CenterX;
	double Ofs_y = PlayerY - Elp->CenterY;
	double After_x = Ofs_x*cos(Elp->Angle) + Ofs_y*sin(Elp->Angle);
	double After_y = ElpSizeX / ElpSizeY * (-Ofs_x*sin(Elp->Angle) + Ofs_y*cos(Elp->Angle));


	DrawFormatString(5, 35, GetColor(0, 255, 255), _T("dist %f"), After_x*After_x + After_y*After_y); // 文字を描画する
	DrawFormatString(305, 35, GetColor(0, 255, 255), _T("elp(x,y) %f,%f"), Elp->CenterX , Elp->CenterY ); // 文字を描画する


	// 原点から移動後点までの距離を算出
	if (After_x*After_x + After_y*After_y <= ElpSizeX*ElpSizeX)
		return true;   // 衝突
	return false;
}