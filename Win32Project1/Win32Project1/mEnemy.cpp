#include "stdafx.h"
#include "mEnemy.h"
#include "Enemy.h"


/*
* �G�I�u�W�F�N�g���Ǘ����邽�߂̃N���X
* ��Փx�̏㏸�E�Ǘ����Ă���G�I�u�W�F�N�g�ւ̓`�B�Ȃǂ��s��
*/
mEnemy::mEnemy(BaseObject* _mEnemyBulletObject, BaseObject*  _PlayerObject) {
	// ����������
	Layer = Layer_EnemyObject; // ���C���ݒ�
	mEnemyBulletObject = _mEnemyBulletObject; // �G�e�Ǘ��I�u�W�F�N�g�ւ̃A�h���X���i�[
	PlayerObjectInstance = _PlayerObject; // �v���C���[�N���X�ւ̃A�h���X���i�[
	Level = 0; // ���x����0�ɐݒ�
	Counter = 0; // ���x���㏸�J�E���^��������

	// �G�I�u�W�F�N�g����
	AddObject(
		new Enemy(_T("Image/enemy1.png"),
		(mEnemyBullet *)mEnemyBulletObject,
		(PlayerObject *)PlayerObjectInstance,
		FieldCenterX,
		FieldCenterY));	
}

mEnemy::~mEnemy()
{
	// �q�I�u�W�F�N�g�̏���
	MyDestructor();
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

	// �v���C���I�u�W�F�N�g�Ƀ��x����`�B
	((PlayerObject*)PlayerObjectInstance)->EnemyLevel = Level;
}

void mEnemy::MyDraw()
{
	// �q�I�u�W�F�N�g�� Draw �֐����Ăяo��
	// ( �����t���O�������Ă������������ )
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
