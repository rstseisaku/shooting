#include "stdafx.h"
#include "Screen.h"


Screen::Screen()
{
}

Screen::Screen(const TCHAR * FileName, int _CenterX, int _CenterY, PlayerObject* Player)
{
	InitCommon(FileName);
	CenterX = _CenterX;
	CenterY = _CenterY;
	PlayerObj = Player;

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
	if (DEBUG)
		DrawFormatString(200, 450, GetColor(0, 255, 255), _T("(Screen)Life %d"), PlayerObj->Life); // •¶Žš‚ð•`‰æ‚·‚é
}

void Screen::MyPeculiarAction(BaseObject * obj) {
	// “Á‚É‚â‚é‚±‚Æ‚Í‚È‚¢
}