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
	// �q�I�u�W�F�N�g��Update���Ăяo��
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
			itr = ObjectList.erase(itr); // �v�f���폜�A���v�f���󂯎��
			continue;
		}
		(*itr)->MyDraw();
		itr++;
	}
}

void mEnemy::MyPeculiarAction(BaseObject * PlayerObj) {
	// ���ɉ������Ȃ�
}
