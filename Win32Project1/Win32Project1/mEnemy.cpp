#include "stdafx.h"
#include "mEnemy.h"
#include "Enemy.h"


mEnemy::mEnemy(BaseObject* _mEnemyBulletObject, BaseObject*  _PlayerObject) {
	Layer = Layer_EnemyObject;
	mEnemyBulletObject = _mEnemyBulletObject;
	PlayerObjectInstance = _PlayerObject;

	/*
	AddObject(
		new Enemy(_T("Image/enemy1.png"),
		(mEnemyBullet *)mEnemyBulletObject,
		(PlayerObject *)PlayerObjectInstance,
		FieldCenterX,
		FieldCenterY));

	AddObject(
		new Enemy2(_T("Image/enemy1.png"),
		(mEnemyBullet *)mEnemyBulletObject,
			(PlayerObject *)PlayerObjectInstance,
			FieldCenterX -170,
			FieldCenterY));
	*/

	AddObject(
		new Enemy2(_T("Image/enemy1.png"),
		(mEnemyBullet *)mEnemyBulletObject,
			(PlayerObject *)PlayerObjectInstance,
			FieldCenterX + 170,
			FieldCenterY));
}

mEnemy::~mEnemy()
{
}

void mEnemy::MyUpdate()
{
	// 子オブジェクトのUpdateを呼び出す
	for (auto itr = ObjectList.begin(); itr != ObjectList.end(); ++itr) {
		if ((*itr)->ObjectDeleteFlag) continue;
		(*itr)->MyUpdate();
	}
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
