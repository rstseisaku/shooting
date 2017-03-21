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
	AddObject(new Bullet2(_T("Image/bullet3.png"), 300, 300, 0, 0));
}

void mEnemyBullet::MyUpdate()
{
	for (auto itr = ObjectList.begin(); itr != ObjectList.end(); ++itr) {
		if ((*itr)->ObjectDeleteFlag) continue;
		(*itr)->MyUpdate();
	}
}

void mEnemyBullet::MyDraw()
{
	for (auto itr = ObjectList.begin(); itr != ObjectList.end(); ++itr) {
		if ((*itr)->ObjectDeleteFlag) continue;
		(*itr)->MyDraw();
	}
}

mEnemyBullet::~mEnemyBullet()
{
}


void mEnemyBullet::MyPeculiarAction(BaseObject * PlayerObj) {
	// プレイヤーオブジェクトを受け取り、当たり判定の処理を行う
	double PlayerObjectCenterX = PlayerObj->CenterX;
	double PlayerObjectCenterY = PlayerObj->CenterY;

	for (auto itr = ObjectList.begin(); itr != ObjectList.end(); ++itr) {
		if ((*itr)->ObjectDeleteFlag) continue;

		if ( ColEllipsPoint(PlayerObjectCenterX, PlayerObjectCenterY, (BaseObject2D*)(*itr) ) ) {
			// 衝突
			// (*itr)->ObjectDelete();
			DrawFormatString(5, 5, GetColor(0, 255, 255), _T("HIT!")); // 文字を描画する

			// 当たったアブジェクト全てに対してHitを呼び出す(引数に対象イテレタ)も
			// 考えられる( Unityとかの仕組み )
			// 今回はプレイヤと敵弾に絞って処理を組む
		}
	}
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