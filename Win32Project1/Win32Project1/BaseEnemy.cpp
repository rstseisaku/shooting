#include "stdafx.h"
#include "BaseEnemy.h"

/*
 * �G�N���X��ݒ肷�邽�߂̃N���X
 * �G�I�u�W�F�N�g�́A���̃N���X���p�����č쐬����
 */
BaseEnemy::BaseEnemy(const TCHAR * FileName, mEnemyBullet * obj, PlayerObject * _PlayerObjectInstance)
{
	// ����������
	InitCommon(FileName); // �t�@�C��������O���t�B�b�N�n���h���E�T�C�Y���擾
	mEnemyBulletObject = obj; // �G�e�Ǘ��I�u�W�F�N�g�ւ̃A�h���X���i�[
	PlayerObjectInstance = _PlayerObjectInstance; // �v���C���[�N���X�ւ̃A�h���X���i�[

	Pattern = NOSELECTED; // �e���p�^�[���𖢑I����Ԃɐݒ�
}

BaseEnemy::BaseEnemy(const TCHAR * FileName, mEnemyBullet * obj, PlayerObject * _PlayerObjectInstance, double _X, double _Y)
{
	// ����������
	InitCommon(FileName); // �t�@�C��������O���t�B�b�N�n���h���E�T�C�Y���擾
	mEnemyBulletObject = obj; // �G�e�Ǘ��I�u�W�F�N�g�ւ̃A�h���X���i�[
	PlayerObjectInstance = _PlayerObjectInstance; // �v���C���[�N���X�ւ̃A�h���X���i�[
	CenterX = _X;
	CenterY = _Y;

	Pattern = NOSELECTED; // �e���p�^�[���𖢑I����Ԃɐݒ�
}

BaseEnemy::~BaseEnemy()
{
}

double BaseEnemy::GetAngleToPlayer() {
	// ���@�ւ̊p�x�����߂�
	double Ans =
		atan2(PlayerObjectInstance->CenterY - CenterY,
			PlayerObjectInstance->CenterX - CenterX);
	Ans = Ans * 180.0 / M_PI; // �x = ���W�A�� �~ 180 �� �~����
	return Ans;
}