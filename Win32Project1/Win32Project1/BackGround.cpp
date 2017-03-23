#include "stdafx.h"
#include "BackGround.h"


BackGround::BackGround()
{
}

BackGround::BackGround(const TCHAR * FileName, int _CenterX, int _CenterY)
{
	InitCommon(FileName);
	CenterX = _CenterX;
	CenterY = _CenterY;

	Layer = Layer_BackGround;
}

BackGround::~BackGround()
{
}

void BackGround::MyUpdate()
{
	CenterY += 1;
	if (CenterY >= 576) {
		CenterY = 0;
	}
}

void BackGround::MyDraw() {
	DrawGraph((int)GetDrawX(), (int)GetDrawY(), GraphicHandle, true);
}

void BackGround::MyPeculiarAction(BaseObject * obj) {
	// “Á‚É‚â‚é‚±‚Æ‚Í‚È‚¢
}