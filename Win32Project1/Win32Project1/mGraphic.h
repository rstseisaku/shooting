#include "stdafx.h"

#pragma once
class mGraphic
{
public:
	mGraphic();
	~mGraphic();
	int MyLoadGraphic(const TCHAR*);
	void MyLoadDivGraphic(const TCHAR*,int splitX,int splitY,int GraphicHanlde[100]);

	// Šù‚É‚ ‚é‰æ‘œ‚Å‚ ‚ê‚ÎCint ‚ğ•Ô‚·
	std::map<const TCHAR*, int> GraphicHandleObject;

	// Šù‚É‚ ‚é‰æ‘œ‚Å‚ ‚ê‚ÎC‚ğ•Ô‚·B(‰æ‘œ–¼‚ÉSplitX,SplitY‚Ìî•ñ‚ğæ‚è‚Ş)
	std::map<const TCHAR*, int> DivGraphicHandleObject;
	int DivImg[100][100];
	int DivImgCounter = 0;
};

