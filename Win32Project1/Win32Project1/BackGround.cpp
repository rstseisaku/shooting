#include "stdafx.h"
#include "BackGround.h"


BackGround::BackGround()
{
}

BackGround::BackGround(const TCHAR * FileName, int _CenterX, int _CenterY)
{
	// 初期化処理
	InitCommon(FileName); // ファイル名からグラフィックハンドル・サイズを取得
	CenterX = _CenterX;
	CenterY = _CenterY;
	LoopPoint = _CenterY; // ループ位置の設定

	Layer = Layer_BackGround; // レイヤの設定
}

BackGround::~BackGround()
{
}

void BackGround::MyUpdate()
{
	// 下方向にスクロールさせる
	CenterY += 1;
	if (CenterY >= LoopPoint) {
		// 一定位置でループさせる
		CenterY = 0;
	}
}

void BackGround::MyDraw() {
	// オブジェクトの画像を表示
	DrawGraph((int)GetDrawX(), (int)GetDrawY(), GraphicHandle, true);
}

void BackGround::MyPeculiarAction(BaseObject * obj) {
	// 特にやることはない
}