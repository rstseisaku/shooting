#include "stdafx.h"
#include "mEnemy.h"
#include "Enemy.h"


mEnemy::mEnemy(BaseObject* _mEnemyBulletObject, BaseObject*  _PlayerObject) {
	Layer = Layer_EnemyObject;
	mEnemyBulletObject = _mEnemyBulletObject;
	PlayerObjectInstance = _PlayerObject;

	AddObject(
		new Enemy(_T("Image/enemy1.png"),
		(mEnemyBullet *)mEnemyBulletObject,
		(PlayerObject *)PlayerObjectInstance,
		FieldCenterX,
		FieldCenterY));

	Level = 0;
	Counter = 0;
}

mEnemy::~mEnemy()
{
}

void mEnemy::MyUpdate()
{
	// 子オブジェクトのUpdateを呼び出す
	for (auto itr = ObjectList.begin(); itr != ObjectList.end(); ++itr) {
		if ((*itr)->ObjectDeleteFlag) continue;
		((Enemy*)(*itr))->mEnemyObjectLevel = Level; // 敵オブジェクトとのレベル同期
		(*itr)->MyUpdate();
	}

	// レベル上昇
	Counter = ((++Counter) % 600);
	if ( Counter == 0) Level++;

	((PlayerObject*)PlayerObjectInstance)->EnemyLevel = Level;
}

void mEnemy::MyDraw()
{
	for (auto itr = ObjectList.begin(); itr != ObjectList.end(); ) {
		if ((*itr)->ObjectDeleteFlag) {
			delete((*itr));
			itr = ObjectList.erase(itr); // 要素を削除、次要素を受け取る
			continue;
		}
		(*itr)->MyDraw();
		itr++;
	}
}

void mEnemy::MyPeculiarAction(BaseObject * PlayerObj) {
	// 特に何もしない
}
