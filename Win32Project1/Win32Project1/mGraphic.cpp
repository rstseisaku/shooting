#include "stdafx.h"
#include "mGraphic.h"


/*
* 読み込んだ画像を管理するクラス
*  _gl_mGraphicObject という名前のグローバル変数として実体化しておく。
* 同じ画像を読み込みに来たら、以前読み込んだハンドルを渡す。
* (キャッシュのような役割を果たす)
*/
mGraphic::mGraphic()
{
}


mGraphic::~mGraphic()
{
}

// 1枚の画像を読み込む
int mGraphic::MyLoadGraphic(const TCHAR* FileName)
{
	int GraphicHandle;

	// FileName という画像を読み込んだことがあるか否かをチェックする
	int res = (int)GraphicHandleObject.count(FileName);
	if ( res == 0) {
			// 未ロードの画像であれば画像の読み込み
			GraphicHandle = LoadGraph(FileName, 0);		if (GraphicHandle == -1) {
			DrawFormatString(0, 70, GetColor(255, 0, 0), _T("【画像読み込みに失敗しました】%s"), FileName); // 文字を描画する
			ScreenFlip();
			WaitKey();
		}
		GraphicHandleObject[FileName] = GraphicHandle;
	} else {
		// ロード済画像であれば、グラフィックハンドルを使いまわす
		GraphicHandle = GraphicHandleObject[FileName];
	}
	return GraphicHandle;
}

void mGraphic::MyLoadDivGraphic(const TCHAR* FileName, int splitX, int splitY, int GraphicHandle[100])
{
	// 画像の分割読み込み
	// 画像ファイルパス・分割数が両方一致していれば、グラフィックハンドルを使いまわす
	int splitId = splitX * splitY;
	int SizeX, SizeY;
	GetImageSize_File(FileName, &SizeX, &SizeY);
	TCHAR FileNameSplitId[200];
	wsprintf(FileNameSplitId, _T("%s_%d"),FileName,splitId);

	// FileName,SplitId に対応する分割画像を読み込んだことがあるか否かをチェックする
	int res = (int)DivGraphicHandleObject.count(FileNameSplitId);
	if ( res == 0) { 
		// 未ロードの画像であれば画像の読み込み
		int res = LoadDivGraph(FileName, splitId, splitX, splitY, SizeX / splitX, SizeY / splitY, DivImg[DivImgCounter]);
		if (res == -1) {
			DrawFormatString(0, 70, GetColor(255, 0, 0), _T("【画像読み込みに失敗しました】%s"), FileName); // 文字を描画する
			ScreenFlip();
			WaitKey();
		}
		DivGraphicHandleObject[FileNameSplitId] = DivImgCounter;
		for (int i = 0; i < 100; i++) {
			GraphicHandle[i] = DivImg[DivImgCounter][i]; 
		}
		DivImgCounter++;
	} else {
		// ロード済画像であれば、グラフィックハンドルを使いまわす
		int tmp = DivGraphicHandleObject[FileNameSplitId];
		for (int i = 0; i < 100; i++) {
			GraphicHandle[i] = DivImg[tmp][i];
		}
	}
}

void mGraphic::MyInitGraph()
{
	// 	読みこんだグラフィックデータをすべて削除
	InitGraph();

	// 画像管理メンバの初期化
	GraphicHandleObject.clear();
	DivGraphicHandleObject.clear();
	DivImgCounter = 0;
}

void mGraphic::MyDeleteGraph(const TCHAR* FileName) 
{
	int res = (int)GraphicHandleObject.count(FileName);
	if (res == 0) {	return; } // 未ロードの画像であれば処理を終了
	else 
	{
		// メモリ開放
		int GraphicHandle;
		GraphicHandle = GraphicHandleObject[FileName];
		DeleteGraph( GraphicHandle );

		//  画像管理メンバから要素を取り除く
		auto itr = GraphicHandleObject.find(FileName);
		if (itr != GraphicHandleObject.end())         // キーの要素が存在している場合
			GraphicHandleObject.erase(itr);
	}
}
