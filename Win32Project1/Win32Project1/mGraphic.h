#include "stdafx.h"

#pragma once
class mGraphic
{
public:
	mGraphic();
	~mGraphic();
	int MyLoadGraphic(const TCHAR*);
	void MyLoadDivGraphic(const TCHAR*,int splitX,int splitY,int GraphicHanlde[100]);

	// ���ɂ���摜�ł���΁Cint ��Ԃ�
	std::map<const TCHAR*, int> GraphicHandleObject;

	// ���ɂ���摜�ł���΁C��Ԃ��B(�摜����SplitX,SplitY�̏�����荞��)
	std::map<const TCHAR*, int> DivGraphicHandleObject;
	int DivImg[100][100];
	int DivImgCounter = 0;
};

