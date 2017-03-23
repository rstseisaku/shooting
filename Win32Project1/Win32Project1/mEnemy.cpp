#include "stdafx.h"
#include "mEnemy.h"
#include "Enemy.h"


mEnemy::mEnemy()
{
}

mEnemy::mEnemy(BaseObject* obj) {
	Layer = Layer_EnemyObject;
	mEnemyBulletObject = obj;

	AddObject(
		new Enemy( _T("Image/PDObject.png"),
					(mEnemyBullet *)mEnemyBulletObject,
					FieldCenterX,
					FieldCenterY ));
}

mEnemy::~mEnemy()
{
}

void mEnemy::MyUpdate()
{
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
