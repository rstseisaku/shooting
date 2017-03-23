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
	double Angle = 0;
	double vAngle = 0;
	int Transparency = 255; // 透過度0をデフォルトとする
	int Mode = DX_BLENDMODE_PMA_ALPHA; // 通常描画をデフォルト
};

