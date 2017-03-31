#include "stdafx.h"
#include "mGraphic.h"


mGraphic::mGraphic()
{
}


mGraphic::~mGraphic()
{
}

int mGraphic::MyLoadGraphic(const TCHAR* FileName)
{
	int GraphicHandle;
	int res = (int)GraphicHandleObject.count(FileName);
	if ( res == 0) { // 未ロードの画像であれば
			GraphicHandle = LoadGraph(FileName, 0);		if (GraphicHandle == -1) {
			DrawFormatString(0, 70, GetColor(255, 0, 0), _T("【画像読み込みに失敗しました】%s"), FileName); // 文字を描画する
			ScreenFlip();
			WaitKey();
		}
		GraphicHandleObject[FileName] = GraphicHandle;
	} else {
		GraphicHandle = GraphicHandleObject[FileName];
	}
	return GraphicHandle;
}

void mGraphic::MyLoadDivGraphic(const TCHAR* FileName, int splitX, int splitY, int GraphicHandle[100])
{
	/*
	 *	LoadDivGraph(char *FileName, int AllNum,
	 *	int XNum, int YNum,
	 *	int XSize, int YSize, int *HandleBuf);
	 */
	int splitId = splitX * splitY;
	int SizeX, SizeY;
	GetImageSize_File(FileName, &SizeX, &SizeY);
	TCHAR FileNameSplitId[200];
	wsprintf(FileNameSplitId, _T("%s_%d"),FileName,splitId);

	int res = (int)DivGraphicHandleObject.count(FileNameSplitId);
	if ( res == 0) { // 未ロードの画像であれば
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
