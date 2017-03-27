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
	LifeGraphic = _gl_mGraphicObject->MyLoadGraphic(_T("Image/life.png"));

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

	ShowLife();
	ShowScore();
	//if (DEBUG)
		//DrawFormatString(600, 200, GetColor(0, 255, 255), _T("(Screen)Life %d"), PlayerObj->Life); // 文字を描画する
		//DrawFormatStringToHandle(600, 400, GetColor(0, 0, 0), ScoreFont, _T("%d"), (int)(TimeScore + GrazeScore + EraseScore)); // スコア
		//DrawFormatString(600, 470, GetColor(0, 0, 0), _T("ボム:%d"), (int)PlayerObj->tmp); // ハイスコア
}

void Screen::MyPeculiarAction(BaseObject * obj) {
	// 特にやることはない
}

void Screen::ShowLife() {
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
	for (int i = 0; i < PlayerObj->Life; i++) {
		DrawGraph(600 + i * 40, 200, LifeGraphic, true);
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
}

void Screen::ShowScore() {
	ScoreLength = GetDrawFormatStringWidthToHandle(ScoreFont,_T("%d"),(int)(TimeScore + GrazeScore + EraseScore));
	DrawFormatStringToHandle(960 - ScoreLength, 400, GetColor(0, 0, 0), ScoreFont, _T("%d"), (int)(TimeScore + GrazeScore + EraseScore)); // スコア
	//DrawFormatString(600, 470, GetColor(0, 0, 0), _T("ボム:%d"), (int)PlayerObj->tmp); // ハイスコア
}