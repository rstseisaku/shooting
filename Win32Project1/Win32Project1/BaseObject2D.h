#pragma once
#include "BaseObject.h"
class BaseObject2D :
	public BaseObject
{
public:
	BaseObject2D();
	~BaseObject2D();
	void InitCommon(const TCHAR * FileName);

	int GraphicHandle; // 画像データのハンドル
};

