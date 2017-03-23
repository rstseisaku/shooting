#pragma once
#include "BaseObject2D.h"
class Screen :
	public BaseObject2D
{
public:
	Screen();
	Screen(const TCHAR * FileName, int _CenterX, int _CenterY);
	~Screen();
	void MyUpdate();
	void MyDraw();
	void MyPeculiarAction(BaseObject * obj);
};

