#include "stdafx.h"
#include "BulletPattern.h"


/*
* �e���ˏo�p�^�[����ݒ肷��N���X
* ( �����Őݒ肵���I�u�W�F�N�g�� mEnemyObject.MakeBullet()�ɓn���C
*   Nway�e�Ȃǂ̃p�^�[���̐������s��
*/
BulletPattern::BulletPattern()
{
	// �K��l��ݒ�
	N = 1; // Nway�e�̐ݒ�
	Angle = 0; // �N�_�ƂȂ�p�x
	vAngle = 0; // Angle�𖈃t���[���ω�������
	vAngleRate = 0.99; // vAngle�ɖ��t���[��������l
	Span = 0; // Nway�e�̊Ԋu
	Speed = 30; // �e�̃X�s�[�h
	X = FieldCenterX; // �ˏo�ʒu
	Y = FieldCenterY; // �ˏo�ʒu
	Transparency = 255; // ���ߓx
	CompositeModeParameter = (int)NORMAL; // �������[�h�̐ݒ�
	FileName = _T("Image/bullet1.png"); // �摜�t�@�C�����̐ݒ�
}


BulletPattern::~BulletPattern()
{
}
