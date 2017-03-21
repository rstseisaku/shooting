#pragma once
#include "BaseObject.h"
class PlayerDecorationObject :
	public BaseObject
{
public:
	PlayerDecorationObject(const TCHAR * FileName);
	PlayerDecorationObject();
	~PlayerDecorationObject();

	void InitCommon(const TCHAR * FileName);

	void MyDraw();
	void MyPeculiarAction(BaseObject * obj);
	void MyUpdate();

	int GraphicHandle;
};

