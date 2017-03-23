#pragma once
#include "BaseObject2D.h"
class BackGround :
	public BaseObject2D
{
public:
	BackGround();
	BackGround(const TCHAR * FileName, int _CenterX, int _CenterY);
	~BackGround();
	void MyUpdate();
	void MyDraw();
	void MyPeculiarAction(BaseObject * obj);
};

