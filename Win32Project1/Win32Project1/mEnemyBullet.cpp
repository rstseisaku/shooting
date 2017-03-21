#include "stdafx.h"

mEnemyBullet::mEnemyBullet()
{
	Layer = Layer_EnemyBullet;

	AddObject(new Bullet(_T("Image/bullet1.png"), 300, 300, 3, 0));
	AddObject(new Bullet(_T("Image/bullet1.png"), 300, 300, -3, 0));
	AddObject(new Bullet(_T("Image/bullet1.png"), 300, 300, 3, 3));
	AddObject(new Bullet(_T("Image/bullet1.png"), 300, 300, 0, 0));

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
	double PlayerObjectCenterX = PlayerObj->GetCenterX();
	double PlayerObjectCenterY = PlayerObj->GetCenterY();

	for (auto itr = ObjectList.begin(); itr != ObjectList.end(); ++itr) {
		if ((*itr)->ObjectDeleteFlag) continue;

		int TargetobjectLayer = (*itr)->Layer;
		// 敵弾管理オブジェクト。当たり判定処理を呼び出す。
		double TargetObjectCenterX = (*itr)->GetCenterX();
		double TargetObjectCenterY = (*itr)->GetCenterY();
		double TargetObjectRadiusX = (*itr)->WidthX * 45 / 100;
		double TargetObjectRadiusY = (*itr)->HeightY * 45 / 100;
		double Distance = std::pow(PlayerObjectCenterX - TargetObjectCenterX, 2.0)
			+ std::pow(PlayerObjectCenterY - TargetObjectCenterY, 2.0);

		if (Distance <= std::pow(TargetObjectRadiusX, 2.0)) {
			// 衝突
			(*itr)->ObjectDelete();

			// 当たったアブジェクト全てに対してHitを呼び出す(引数に対象イテレタ)も
			// 考えられる( Unityとかの仕組み )
			// 今回はプレイヤと敵弾に絞って処理を組む
		}
	}
}
