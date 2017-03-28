#include "stdafx.h"

bool comp(BaseObject *& v1, BaseObject *& v2) {
	if (v1->Layer < v2->Layer) {
		return true;
	}
	else {
		return false;
	}
}

// �R���X�g���N�^
mGameObject::mGameObject()
{
	GameStatus = GAMESTART;
}

mGameObject::~mGameObject()
{
}

void mGameObject::MyUpdate()
{
	_gl_KeyControlObject->Update(); // �L�[�{�[�h��ԍX�V
	if (GameStatus == GAMEPLAYING) {
		MyUpdateGameplaying();
	}
	else if (GameStatus == GAMEOVER) {
		MyUpdateGameover();
	}
	else if (GameStatus == GAMESTART) {
		MyUpdateGamestart();
	}
}

void mGameObject::MyDraw()
{
	for (auto itr = ObjectList.begin(); itr != ObjectList.end(); ++itr) {
		if ((*itr)->ObjectDeleteFlag) continue;
		(*itr)->MyDraw();
	}
	// DrawFormatString(x, y, GetColor(0, 255, 255), _T("Obj��[%d]"),  ObjectList.size() ); // ������`�悷��
}

void mGameObject::AddObject(BaseObject *obj)
{
	ObjectList.push_back(obj);
}

void mGameObject::ClearObject()
{
	// �o�^���Ă���I�u�W�F�N�g������
	// (ObjectList.Clear�͎q�I�u�W�F�N�g�������Ȃ��̂Ŏg��Ȃ�)
	for (auto itr = ObjectList.begin(); itr != ObjectList.end(); ) {
		int ObjectLayer = (*itr)->Layer;
		delete((*itr)); // �f�X�g���N�^�̒��ŁA�K�v�ɉ����Ďq�I�u�W�F�N�g�������������
		itr = ObjectList.erase(itr); // �v�f���폜�A���v�f���󂯎��
	}
}

// GameStatus�ɉ����ăI�u�W�F�N�g��ݒu
void mGameObject::SetObject()
{
	if (GameStatus == GAMESTART) {
		// GAMESTART�J�n���ɕK�v�Ȃ��̂��Z�b�g
		// (���ɂȂ�)
	}
	else if (GameStatus == GAMEPLAYING) {
		// �Q�[���v���C�J�n���ɕK�v�Ȃ��̂��Z�b�g
		mEnemyBulletObject = new mEnemyBullet();
		Player = new PlayerObject(_T("Image/PlayerObject.png"), 0, 0, mEnemyBulletObject); // �v���C���[�I�u�W�F�N�g
		AddObject(mEnemyBulletObject); // �G�e�Ǘ��I�u�W�F�N�g
		AddObject(new mEnemy(mEnemyBulletObject, Player)); // �G�Ǘ��I�u�W�F�N�g�B�G�e�Ǘ��I�u�W�F�N�g���ꏏ�ɓn���B
		AddObject(new PlayerDecorationObject(_T("Image/PDObject.png"))); // �v���C���[�̓����蔻���\��
		AddObject(Player);
		AddObject(new BackGround(_T("Image/BackGround1.png"), 288, 576)); // �w�i�I�u�W�F�N�g
		mScreen = new Screen(_T("Image/Screen.png"), 512, 288, Player);
		AddObject(mScreen);
		ObjectList.sort(&comp);
	}
	else if (GameStatus == GAMEOVER) {
		// �Q�[���I�[�o�[�J�n���ɕK�v�Ȃ��̂��Z�b�g
		// �S�Ŏ��̔w�i��\��
		AddObject(new BackGround(_T("Image/gameover.png"), WindowCenterX, WindowCenterY));
	}

}

// �Q�[����Ԃ̏�ԑJ�ځB
// �I�u�W�F�N�g�̍Ĕz�u���s���B
void mGameObject::ChangeStatus(int Status)
{
	GameStatus = Status; // GameStatus��GAMEOVER�ɐ؂�ւ���
	ClearObject();
	SetObject();
}


/*
* =====================================================
* Status�ɉ�����Update����
* =====================================================
*/

// GameStatus��Gamestart�Ȃ�Ăяo�������B
// �Q�[���̏�����������S������B
void mGameObject::MyUpdateGamestart()
{
	// �����������B�I����A���̂܂܃v���C����ԂɑJ��
	_gl_KeyControlObject->Init();
	_gl_mSoundObject->MyPlaySoundMem(_T("Sound/BGM1.mp3"), DX_PLAYTYPE_LOOP);
	x = 0;
	y = 0;

	// �v���C����ԂɃ`�F���W�B
	ChangeStatus(GAMEPLAYING);
}

// GameStatus��GameOver�Ȃ�Ăяo�������B
// �Q�[���̏I��������S������B
void mGameObject::MyUpdateGameover()
{
	// �Q�[���I�[�o�[��ʂł̏���
	if (_gl_KeyControlObject->Key[KEY_INPUT_ESCAPE] == 1)
		ChangeStatus(GAMESTART);
}

// GameStatus��GamePlaying�Ȃ�Ăяo�������B
// �Q�[���̃��C��������S������B
void mGameObject::MyUpdateGameplaying()
{
	// ���ꂼ��̃I�u�W�F�N�g��Update�֐����Ăяo��
	for (auto itr = ObjectList.begin(); itr != ObjectList.end(); ++itr) {
		if ((*itr)->ObjectDeleteFlag) continue;
		(*itr)->MyUpdate();
	}

	// �Q�[���I�[�o�[����
	if (Player->Life == -1) {
		_gl_mSoundObject->MyPlaySoundMem(_T("Sound/BGM2.mp3"), DX_PLAYTYPE_LOOP);
		ChangeStatus(GAMEOVER);
		return;
	}

	bool isExistItem = false;
	bool isExistBomItem = false;
	bool isExistRareItem = false;
	// �J�e�S���ɉ��������ꏈ��
	//  PlayerObject �� �Փ˔���
	//  ItemObject �� ���݂��邱�Ƃ�ۑ�
	for (auto PlayerItr = ObjectList.begin(); PlayerItr != ObjectList.end(); ++PlayerItr) {
		if ((*PlayerItr)->ObjectDeleteFlag) continue;
		int ObjectLayer = (*PlayerItr)->Layer;

		// �A�C�e���I�u�W�F�N�g�Q�́A�v���C���Ƃ̋������r�����݂������Ƃ�����
		if (ObjectLayer == Layer_Item) isExistItem = true;
		if (ObjectLayer == Layer_RareItem) isExistRareItem = true;
		if (ObjectLayer == Layer_BomItem) isExistBomItem = true;

		// �v���C���[�I�u�W�F�N�g����������(1�̂�)
		if ( ObjectLayer == Layer_PlayerObject ) {
			// �e�I�u�W�F�N�g�Ƃ̏Փ˔�����s��
			for (auto itr = ObjectList.begin(); itr != ObjectList.end(); ++itr) {
				if ((*itr)->ObjectDeleteFlag) continue;

				// ���背�C���̃I�u�W�F�N�g�ƁAPeculiarAcytion���s��
				int TargetobjectLayer = (*itr)->Layer;
				if (TargetobjectLayer == Layer_EnemyBullet ||
					TargetobjectLayer == Layer_PlayerDecorationObject ||
					TargetobjectLayer == Layer_Item ||
					TargetobjectLayer == Layer_BomItem ||
					TargetobjectLayer == Layer_RareItem ) {
					// �E�G�e�Ǘ��I�u�W�F�N�g�B
					//  �@�\�G�e�Ǘ��I�u�W�F�N�g�́A�ŗL�����́A�ۗL�o���b�g�Ƃ̓����蔻��)
					// �E�f�R���[�g�I�u�W�F�N�g
					//  �@�\���W�����킹�邾��)
					// �E�A�C�e���n
					// �@ �\�Փ˔�����s��
					(*itr)->MyPeculiarAction((*PlayerItr));
				}
			}
		}
	}

	// �A�C�e���I�u�W�F�N�g�����ł��Ă���ꍇ
	if (!isExistItem && !isExistBomItem) {
		int ItemX = GetRand(MoveableWidth/2) + (MoveableWidth / 2) * isItemRight;
		int ItemY = GetRand( MoveableAreaButtom / 3) + MoveableAreaButtom * 2 / 3;
		ItemObject* tmp = new ItemObject(_T("Image/Item.png"), ItemX, ItemY, Layer_Item);
		tmp->Mode = ADD;
		tmp->Transparency = 180;
		AddObject( tmp );
		ObjectList.sort(&comp);

		isItemRight = (++isItemRight) % 2;
	}

	if (!isExistRareItem) {
		int ItemX = GetRand( ( MoveableWidth - 48) / 2) + 24 + (MoveableWidth / 2) * isRareItemRight;
		int ItemY = GetRand( MoveableAreaButtom / 3 ) + MoveableAreaUpper + 42;
		ItemObject* tmp = new ItemObject(_T("Image/RareItem.png"), ItemX, ItemY, Layer_RareItem);
		tmp->Mode = ADD;
		tmp->Transparency = 180;
		AddObject(tmp);
		ObjectList.sort(&comp);

		isRareItemRight = (++isRareItemRight) % 2;
	}
}

