#include "stdafx.h"
#include "Bullet2.h"


Bullet2::Bullet2()
{
}

Bullet2::Bullet2(const TCHAR * FileName)
{
	// ����������
	InitCommon(FileName); // �t�@�C��������O���t�B�b�N�n���h���E�T�C�Y���擾
}

Bullet2::Bullet2(const TCHAR * FileName, int _Angle, int _Speed)
{
	// ����������
	InitCommon(FileName); // �t�@�C��������O���t�B�b�N�n���h���E�T�C�Y���擾
	Angle = _Angle % 360; // 0-360�Ɏ��߂�
	Speed = _Speed / 60.0; // 1�b�ԂɈړ�����l���A1�t���[��������̒l�ɕϊ�����
}

Bullet2::Bullet2(const TCHAR * FileName, int _x, int _y, int _Angle, int _Speed)
{
	// ����������
	InitCommon(FileName); // �t�@�C��������O���t�B�b�N�n���h���E�T�C�Y���擾
	Angle = _Angle % 360; // 0-360�Ɏ��߂�
	Speed = _Speed / 60.0; // 1�b�ԂɈړ�����l���A1�t���[��������̒l�ɕϊ�����
	CenterX = _x;
	CenterY = _y;
}

Bullet2::Bullet2(const TCHAR * FileName, int _x, int _y, int _Angle, int _Speed, 
				 int _Mode, int _Transparency )
{
	// ����������
	InitCommon(FileName); // �t�@�C��������O���t�B�b�N�n���h���E�T�C�Y���擾
	Angle = _Angle % 360; // 0-360�Ɏ��߂�
	Speed = _Speed / 60.0; // 1�b�ԂɈړ�����l���A1�t���[��������̒l�ɕϊ�����
	CenterX = _x;
	CenterY = _y;
	Mode = _Mode; // �A���t�@�u�����h�l
	Transparency = _Transparency; // ���ߓx�̐ݒ�
}

Bullet2::~Bullet2()
{
	// �q�I�u�W�F�N�g�̏���
	MyDestructor();
}

void Bullet2::MyUpdate() {
	// �t�F�[�h�A�E�g���n�܂��Ă�����A�������~����
	if (MyFadeout()) return;

	// ���݂̊p�x�E�X�s�[�h�����ƂɈړ�����֐�( Speed�CAngle, vAngle, vAngleRate )
	MoveFromAngle();
}

void Bullet2::MyDraw() {
	// �I�u�W�F�N�g�̉摜��\��
	SetDrawBlendMode(Mode, Transparency);
	DrawRotaGraph((int)CenterX , (int)CenterY, 1.0, Angle / 180 * M_PI,
		GraphicHandle, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
}

void Bullet2::MyPeculiarAction(BaseObject * obj)
{
	// ���ɂ�邱�Ƃ͂Ȃ�
}
