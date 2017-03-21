#include "stdafx.h"


Bullet::Bullet()
{
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
	// “Á‚É‚â‚é‚±‚Æ‚Í‚È‚¢
}
