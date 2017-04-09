#include "stdafx.h"
#include "Screen.h"


Screen::Screen()
{
}

Screen::Screen(const TCHAR * FileName, int _CenterX, int _CenterY, PlayerObject* Player)
{
	// 初期化処理
	InitCommon(FileName); // ファイル名からグラフィックハンドル・サイズを取得
	CenterX = _CenterX;
	CenterY = _CenterY;
	PlayerObj = Player; // プレイヤーオブジェクトのインスタンス保持

	ScoreFont = CreateFontToHandle(NULL, 64, 3); // スコアフォントの設定ハンドルの取得
	LifeGraphic = _gl_mGraphicObject->MyLoadGraphic(_T("Image/life.png")); // ライフ画像読み込み

	Layer = Layer_Screen; // レイヤ設定
}

Screen::~Screen()
{
	// 子オブジェクトの消去
	MyDestructor();
}

void Screen::MyUpdate()
{
	// 各スコアを加算していく
	TimeScore += 1.0 / 60; // 時間経過によるスコア上昇
	GrazeScore = PlayerObj->GrazeScore; // グレイズスコア読み込み
	EraseScore = PlayerObj->EraseScore; // ボムによるスコア読み込み
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