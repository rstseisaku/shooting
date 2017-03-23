#include "stdafx.h"

bool comp(BaseObject *& v1, BaseObject *& v2) {
	if (v1->Layer < v2->Layer) {
		return true;
	}
	else {
		return false;
	}
}

// ObjectList.sort(&comp);

mGameObject::mGameObject()
{
	_gl_KeyControlObject->Init();
	x = 0;
	y = 0;

	// �I�u�W�F�N�g�𐶐�
	AddObject(new mEnemyBullet()); // �G�e�Ǘ��I�u�W�F�N�g
	AddObject(new PlayerDecorationObject(_T("Image/PDObject.png"))); // �v���C���[�f�R���[�g�I�u�W�F�N�g
	AddObject(new PlayerObject(_T("Image/PlayerObject.png"), 0, 0)); // �v���C���[�I�u�W�F�N�g
	AddObject(new BackGround(_T("Image/BackGround1.png"), 288, 576)); // �w�i�I�u�W�F�N�g
	AddObject(new Screen(_T("Image/Screen.png"), 512, 288)); // �w�i�I�u�W�F�N�g

	ObjectList.sort( &comp );
}

mGameObject::~mGameObject()
{
}

void mGameObject::MyUpdate()
{
	// ���ꂼ��̃I�u�W�F�N�g��Update�֐����Ăяo��
	_gl_KeyControlObject->Update();
	for (auto itr = ObjectList.begin(); itr != ObjectList.end(); ++itr) {
		if ( (*itr)->ObjectDeleteFlag ) continue;
		(*itr)->MyUpdate();
	}
	DrawFormatString(5, 85, GetColor(0, 255, 255), _T("OK")); // ������`�悷��

	// �Փ˔�����s��
	// �J�e�S����T�������Ȃ̂ŁA�������ȊO�͂����܂ŏd���Ȃ��͂�
	// (�C�e���[�^�̒��g�̓|�C���^)
	for (auto PlayerItr = ObjectList.begin(); PlayerItr != ObjectList.end(); ++PlayerItr) {
		if ( (*PlayerItr)->ObjectDeleteFlag ) continue;

		// �v���C���[�I�u�W�F�N�g����������(1�̂�)
		int ObjectLayer = (*PlayerItr)->Layer;
		if (ObjectLayer == Layer_PlayerObject) {

			// �e�I�u�W�F�N�g�Ƃ̏Փ˔�����s��
			for (auto itr = ObjectList.begin(); itr != ObjectList.end(); ++itr) {
				if ( (*itr)->ObjectDeleteFlag ) continue;

				int TargetobjectLayer = (*itr)->Layer;
				if (TargetobjectLayer == Layer_EnemyBullet || 
					TargetobjectLayer == Layer_PlayerDecorationObject) {
					// �G�e�Ǘ��I�u�W�F�N�g�B
					//  (�G�e�Ǘ��I�u�W�F�N�g�́A�ŗL�����́A�ۗL�o���b�g�Ƃ̓����蔻��)
					// �f�R���[�g�I�u�W�F�N�g
					//  (���W�����킹�邾��)
					(*itr)->MyPeculiarAction((*PlayerItr));
				}
			}
		}
	}
}

void mGameObject::MyDraw()
{
	for (auto itr = ObjectList.begin(); itr != ObjectList.end(); ++itr) {
		if ( (*itr)->ObjectDeleteFlag ) continue;
		(*itr)->MyDraw();
	}
	// DrawFormatString(x, y, GetColor(0, 255, 255), _T("Obj��[%d]"),  ObjectList.size() ); // ������`�悷��
}

void mGameObject::AddObject( BaseObject *obj )
{
	ObjectList.push_back(obj);
}

