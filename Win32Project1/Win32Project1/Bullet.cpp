#include "stdafx.h"


Bullet::Bullet()
{
	// 画像のない弾オブジェクト
	// 編集テスト! 2017_0321_1517
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

// 「全てのオブジェクトが画像を持つ」と設計すれば、
// この処理は「ベースオブジェクト」に移せる
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
	// 特にやることはない
}
