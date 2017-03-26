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

Bullet::Bullet(const TCHAR * FileName, int _CenterX, int _CenterY, double _vx, double _vy)
{
	InitCommon(FileName);
	CenterX = _CenterX;
	CenterY = _CenterY;
	vx = _vx;
	vy = _vy;
}

Bullet::Bullet(const TCHAR * FileName, int _CenterX, int _CenterY,
	double _vx, double _vy, double _vvx, double _vvy)
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

	// äpìxÇÃçXêV
	Angle = atan2(vy, vx);
	Angle = Angle * 180.0 / M_PI;
}

void Bullet::MyDraw() {
	SetDrawBlendMode(Mode, Transparency);
	DrawRotaGraph((int)CenterX, (int)CenterY, 1.0, Angle / 180 * M_PI,
		GraphicHandle, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
}

void Bullet::MyPeculiarAction(BaseObject * obj) {
	// ì¡Ç…Ç‚ÇÈÇ±Ç∆ÇÕÇ»Ç¢
}
