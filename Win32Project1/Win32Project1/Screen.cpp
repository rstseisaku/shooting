#include "stdafx.h"
#include "Screen.h"


Screen::Screen()
{
}

Screen::Screen(const TCHAR * FileName, int _CenterX, int _CenterY)
{
	InitCommon(FileName);
	CenterX = _CenterX;
	CenterY = _CenterY;

	Layer = Layer_Screen;
}

Screen::~Screen()
{
}

void Screen::MyUpdate()
{
}

void Screen::MyDraw() {
	DrawGraph((int)GetDrawX(), (int)GetDrawY(), GraphicHandle, true);
}

void Screen::MyPeculiarAction(BaseObject * obj) {
	// “Á‚É‚â‚é‚±‚Æ‚Í‚È‚¢
}