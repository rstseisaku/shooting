#pragma once
#include "stdafx.h"

class Bullet :
	public BaseObject
{
public:
	Bullet();
	Bullet(const TCHAR * FileName);
	Bullet(const TCHAR * FileName, int _LeftX, int _UpperY);
	Bullet(const TCHAR * FileName, int _LeftX, int _UpperY, int _vx, int _vy);
	Bullet(const TCHAR * FileName, int _LeftX, int _UpperY, int _vx, int _vy, int _vvx, int _vvy);
	~Bullet();

	void InitCommon(const TCHAR * FileName);

	void MyDraw();
	void MyPeculiarAction(BaseObject * obj);
	void MyUpdate();

	int GraphicHandle; // 敵弾のデータ(画像)

	// ( とりあえずシンプルな方法で )
	int angle;
	int speed;
	double vx;
	double vy;
	double vvx;
	double vvy;
};

