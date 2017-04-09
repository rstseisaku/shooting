#include "stdafx.h"


Bullet::Bullet()
{
}


Bullet::Bullet(const TCHAR * FileName)
{
	// ����������
	InitCommon(FileName); // �t�@�C��������O���t�B�b�N�n���h���E�T�C�Y���擾
}

Bullet::Bullet(const TCHAR * FileName, int _CenterX, int _CenterY)
{
	// ����������
	InitCommon(FileName); // �t�@�C��������O���t�B�b�N�n���h���E�T�C�Y���擾
	CenterX = _CenterX;
	CenterY = _CenterY;
}

Bullet::Bullet(const TCHAR * FileName, int _CenterX, int _CenterY, double _vx, double _vy)
{
	// ����������
	InitCommon(FileName); // �t�@�C��������O���t�B�b�N�n���h���E�T�C�Y���擾
	CenterX = _CenterX;
	CenterY = _CenterY;
	vx = _vx;
	vy = _vy;
}

Bullet::Bullet(const TCHAR * FileName, int _CenterX, int _CenterY,
	double _vx, double _vy, double _vvx, double _vvy)
{
	// ����������
	InitCommon(FileName); // �t�@�C��������O���t�B�b�N�n���h���E�T�C�Y���擾
	CenterX = _CenterX;
	CenterY = _CenterY;
	vx = _vx;
	vy = _vy;
	vvx = _vvx; // �����xx
	vvy = _vvy; // �����xy
}

Bullet::~Bullet()
{
	// �q�I�u�W�F�N�g�̏���
	MyDestructor();
}

void Bullet::MyUpdate()
{
	// �t�F�[�h�A�E�g���n�܂��Ă�����A�������~����
	if (MyFadeout()) return;

	// �����x�E���x�𔽉f���A�ړ�������
	vx += vvx;
	vy += vvy;
	CenterX += vx;
	CenterY += vy;

	// �p�x�̍X�V
	Angle = atan2(vy, vx);
	Angle = Angle * 180.0 / M_PI;

	// ��O�I�u�W�F�N�g�폜
	if (CenterX < MoveableAreaLeft - 100) ObjectDeleteFlag = true;
	if (CenterY < MoveableAreaUpper - 100) ObjectDeleteFlag = true;
	if (CenterX > MoveableAreaRight + 100) ObjectDeleteFlag = true;
	if (CenterY > MoveableAreaButtom + 100) ObjectDeleteFlag = true;
}

void Bullet::MyDraw() {
	// �I�u�W�F�N�g�̉摜��\��
	SetDrawBlendMode(Mode, Transparency);
	DrawRotaGraph((int)CenterX, (int)CenterY, 1.0, Angle / 180 * M_PI,
		GraphicHandle, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
}

void Bullet::MyPeculiarAction(BaseObject * obj) {
	// ���ɂ�邱�Ƃ͂Ȃ�
}
