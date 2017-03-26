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

	ScoreFont = CreateFontToHandle(NULL, 64, 3);

	Layer = Layer_Screen;
}

Screen::~Screen()
{
}

void Screen::MyUpdate()
{
	TimeScore += 1.0 / 60;
	GrazeScore = PlayerObj->GrazeScore;
	EraseScore = PlayerObj->EraseScore;
}

void Screen::MyDraw() {
	DrawGraph((int)GetDrawX(), (int)GetDrawY(), GraphicHandle, true);
	if (DEBUG)
		DrawFormatString(600, 200, GetColor(0, 255, 255), _T("(Screen)Life %d"), PlayerObj->Life); // 文字を描画する
		DrawFormatStringToHandle(600, 400, GetColor(0, 0, 0), ScoreFont, _T("%d"), (int)(TimeScore + GrazeScore + EraseScore)); // スコア
		//DrawFormatString(600, 470, GetColor(0, 0, 0), _T("ボム:%d"), (int)PlayerObj->tmp); // ハイスコア
}

void Screen::MyPeculiarAction(BaseObject * obj) {
	// 特にやることはない
}