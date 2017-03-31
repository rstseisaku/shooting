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
	MyDestructor();
}

void Bullet::MyUpdate()
{
	if (MyFadeout()) return; // フェードアウトの判定・処理

	vx += vvx;
	vy += vvy;
	CenterX += vx;
	CenterY += vy;

	// 角度の更新
	Angle = atan2(vy, vx);
	Angle = Angle * 180.0 / M_PI;

	if (CenterX < MoveableAreaLeft - 100) ObjectDeleteFlag = true;
	if (CenterY < MoveableAreaUpper - 100) ObjectDeleteFlag = true;
	if (CenterX > MoveableAreaRight + 100) ObjectDeleteFlag = true;
	if (CenterY > MoveableAreaButtom + 100) ObjectDeleteFlag = true;
}

void Bullet::MyDraw() {
	SetDrawBlendMode(Mode, Transparency);
	DrawRotaGraph((int)CenterX, (int)CenterY, 1.0, Angle / 180 * M_PI,
		GraphicHandle, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
}

void Bullet::MyPeculiarAction(BaseObject * obj) {
	// 特にやることはない
}
