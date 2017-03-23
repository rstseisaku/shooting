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
	Angle = _Angle;
	Speed = _Speed;
}

Bullet2::Bullet2(const TCHAR * FileName, int _x, int _y, int _Angle, int _Speed)
{
	InitCommon(FileName); // �摜�n���h�� WidthX HeightY�̎Z�o
	Angle = _Angle;
	Speed = _Speed / 60;
	CenterX = _x;
	CenterY = _y;
}

Bullet2::Bullet2(const TCHAR * FileName, int _x, int _y, int _Angle, int _Speed, 
				 int _Mode, int _Transparency )
{
	InitCommon(FileName); // �摜�n���h�� WidthX HeightY�̎Z�o
	Angle = _Angle;
	Speed = _Speed / 60;
	CenterX = _x;
	CenterY = _y;
	Mode = _Mode;
	Transparency = _Transparency;
}

Bullet2::~Bullet2()
{
}

void Bullet2::MyUpdate() {	
	CenterX += cos(Angle) * Speed;
	CenterY += sin(Angle) * Speed;
	Angle += M_PI / 360;
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

	Transparency = 127;
	SetDrawBlendMode(DX_BLENDMODE_PMA_ADD, Transparency);
	DrawRotaGraph((int)CenterX , (int)CenterY, 1.0,  Angle,
		GraphicHandle, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

}

void Bullet2::MyPeculiarAction(BaseObject * obj)
{
}