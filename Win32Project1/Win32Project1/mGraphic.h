#include "stdafx.h"

#pragma once
class mGraphic
{
public:
	mGraphic();
	~mGraphic();
	int MyLoadGraphic(const TCHAR*);
	void MyLoadDivGraphic(const TCHAR*,int splitX,int splitY,int GraphicHanlde[100]);
	void MyInitGraph();

	void MyDeleteGraph(const TCHAR * FileName);

	// 既にある画像であれば，int を返す
	std::map<const TCHAR*, int> GraphicHandleObject;

	// 既にある画像であれば，を返す。(画像名にSplitX,SplitYの情報を取り込む)
	std::map<const TCHAR*, int> DivGraphicHandleObject;
	int DivImg[100][100];
	int DivImgCounter = 0;
};

