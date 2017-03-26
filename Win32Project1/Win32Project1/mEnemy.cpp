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
	// �q�I�u�W�F�N�g��Update���Ăяo��
	for (auto itr = ObjectList.begin(); itr != ObjectList.end(); ++itr) {
		if ((*itr)->ObjectDeleteFlag) continue;
		((Enemy*)(*itr))->mEnemyObjectLevel = Level; // �G�I�u�W�F�N�g�Ƃ̃��x������
		(*itr)->MyUpdate();
	}

	// ���x���㏸
	Counter = ((++Counter) % 600);
	if ( Counter == 0) Level++;

	((PlayerObject*)PlayerObjectInstance)->EnemyLevel = Level;
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
