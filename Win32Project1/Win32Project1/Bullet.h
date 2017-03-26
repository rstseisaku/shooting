#pragma once
#include "stdafx.h"

class Bullet :
	public BaseObject2D
{
public:
	Bullet();
	Bullet(const TCHAR * FileName);
	Bullet(const TCHAR * FileName, int _LeftX, int _UpperY);
	Bullet(const TCHAR * FileName, int _LeftX, int _UpperY, double _vx, double _vy);
	Bullet(const TCHAR * FileName, int _LeftX, int _UpperY, double _vx, double _vy, double _vvx, double _vvy);
	~Bullet();

	void MyDraw();
	void MyPeculiarAction(BaseObject * obj);
	void MyUpdate();

	// ( ‚Æ‚è‚ ‚¦‚¸ƒVƒ“ƒvƒ‹‚È•û–@‚Å )
	double vx;
	double vy;
	double vvx;
	double vvy;
	double Angle;
};

