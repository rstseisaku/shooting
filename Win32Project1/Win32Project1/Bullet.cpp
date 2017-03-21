#include "stdafx.h"


Bullet::Bullet()
{
	// �摜�̂Ȃ��e�I�u�W�F�N�g
	// �ҏW�e�X�g! 2017_0321_1517
}


Bullet::Bullet(const TCHAR * FileName)
{
	InitCommon(FileName);
}

Bullet::Bullet(const TCHAR * FileName, int _CenterX, int _CenterY)
{
	InitCommon(FileName);
	CenterX = _CenterX;
	CenterY = _CenterY;
}

Bullet::Bullet(const TCHAR * FileName, int _CenterX, int _CenterY, int _vx,int _vy)
{
	InitCommon(FileName);
	CenterX = _CenterX;
	CenterY = _CenterY;
	vx = _vx;
	vy = _vy;
}

Bullet::Bullet(const TCHAR * FileName, int _CenterX, int _CenterY, int _vx, int _vy,int _vvx,int _vvy)
{
	InitCommon(FileName);
	CenterX = _CenterX;
	CenterY = _CenterY;
	vx = _vx;
	vy = _vy;
	vvx = _vvx;
	vvy = _vvy;
}

Bullet::~Bullet()
{
}

// �u�S�ẴI�u�W�F�N�g���摜�����v�Ɛ݌v����΁A
// ���̏����́u�x�[�X�I�u�W�F�N�g�v�Ɉڂ���
void Bullet::InitCommon(const TCHAR *FileName) {
	GraphicHandle = _gl_mGraphicObject->MyLoadGraphic(FileName);
	GetGraphSize(GraphicHandle, &WidthX, &HeightY);
}

void Bullet::MyUpdate()
{
	vx += vvx;
	vy += vvy;
	CenterX += vx;
	CenterY += vy;
}

void Bullet::MyDraw() {
	DrawGraph((int)GetDrawX(), (int)GetDrawY(), GraphicHandle, true);
}

void Bullet::MyPeculiarAction(BaseObject * obj) {
	// ���ɂ�邱�Ƃ͂Ȃ�
}
