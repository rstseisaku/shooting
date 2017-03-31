#include "stdafx.h"
#include "Bullet2.h"


Bullet2::Bullet2()
{
}

Bullet2::Bullet2(const TCHAR * FileName)
{
	InitCommon(FileName); // �摜�n���h�� WidthX HeightY�̎Z�o
}

Bullet2::Bullet2(const TCHAR * FileName, int _Angle, int _Speed)
{
	InitCommon(FileName); // �摜�n���h�� WidthX HeightY�̎Z�o
	Angle = _Angle % 360;
	Speed = _Speed / 60.0;
}

Bullet2::Bullet2(const TCHAR * FileName, int _x, int _y, int _Angle, int _Speed)
{
	InitCommon(FileName); // �摜�n���h�� WidthX HeightY�̎Z�o
	Angle = _Angle % 360;
	Speed = _Speed / 60.0;
	CenterX = _x;
	CenterY = _y;
}

Bullet2::Bullet2(const TCHAR * FileName, int _x, int _y, int _Angle, int _Speed, 
				 int _Mode, int _Transparency )
{
	InitCommon(FileName); // �摜�n���h�� WidthX HeightY�̎Z�o
	Angle = _Angle % 360;
	Speed = _Speed / 60.0;
	CenterX = _x;
	CenterY = _y;
	Mode = _Mode;
	Transparency = _Transparency;
}

Bullet2::~Bullet2()
{
	MyDestructor();
}

void Bullet2::MyUpdate() {
	if (MyFadeout()) return; // �t�F�[�h�A�E�g�̔���E����
	MoveFromAngle();
}

void Bullet2::MyDraw() {
	/*
	�錾	int DrawRotaGraph(int x, int y, double ExtRate, double Angle,
		int GrHandle, int TransFlag);

	�T��	�������ɓǂ݂��񂾃O���t�B�b�N�̉�]�`��

		����	x, y�@�@�@: �O���t�B�b�N��`�悷��̈�̒��S���W
		ExtRate�@�@ : �g�嗦�i�P.�O�œ��{�j
		Angle�@�@�@ : �`��p�x�i���W�A���w��j
		GrHandle�@ : �`�悷��O���t�B�b�N�̎��ʔԍ��i�O���t�B�b�N�n���h���j
		TransFlag�@ : ���ߐF���L�����A�t���O�iTRUE�ŗL��FALSE�Ŗ����j
	*/

	/*
	//��Z�ς݃A���t�@�p�̃A���t�@�u�����h
    DX_BLENDMODE_PMA_ALPHA

    // ��Z�ς݃A���t�@�p�̉��Z�u�����h
    DX_BLENDMODE_PMA_ADD

    // ��Z�ς݃A���t�@�p�̌��Z�u�����h
    DX_BLENDMODE_PMA_SUB
	*/

	SetDrawBlendMode(Mode, Transparency);
	DrawRotaGraph((int)CenterX , (int)CenterY, 1.0, Angle / 180 * M_PI,
		GraphicHandle, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);


	//DrawFormatString(100, 400, GetColor(0, 255, 255), _T("angle %f"), Angle); // ������`�悷��
}

void Bullet2::MyPeculiarAction(BaseObject * obj)
{
}
