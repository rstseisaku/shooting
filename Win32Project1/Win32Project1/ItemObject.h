#pragma once
#include "BaseObject2D.h"
class ItemObject :
	public BaseObject2D
{
public:
	ItemObject(const TCHAR * FileName, int _CenterX, int _CenterY, int _Layer);
	~ItemObject();

	void MyUpdate();
	void MyDraw();
	void MyPeculiarAction(BaseObject* obj);
};

