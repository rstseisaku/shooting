#pragma once
#include "BaseObject.h"
class Bullet2 :
	public BaseObject2D
{
public:
	Bullet2();
	Bullet2(const TCHAR * FileName);
	Bullet2(const TCHAR * FileName, int Angle, int Speed);
	Bullet2(const TCHAR * FileName, int _x, int _y, int _Angle, int _Speed);
	Bullet2(const TCHAR * FileName, int _x, int _y, int _Angle, int _Speed, int _Mode, int _Transparency);
	~Bullet2();

	void MyUpdate();
	void MyDraw();
	void MyPeculiarAction(BaseObject * obj);

	int Speed;
};

