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
	int res = GraphicHandleObject.count(FileName);
	if ( res == 0) { // –¢ƒ[ƒh‚Ì‰æ‘œ‚Å‚ ‚ê‚Î
			GraphicHandle = LoadGraph(FileName, 0);		if (GraphicHandle == -1) {
			DrawFormatString(0, 70, GetColor(255, 0, 0), _T("y‰æ‘œ“Ç‚İ‚İ‚É¸”s‚µ‚Ü‚µ‚½z%s"), FileName); // •¶š‚ğ•`‰æ‚·‚é
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

	int res = DivGraphicHandleObject.count(FileNameSplitId);
	if ( res == 0) { // –¢ƒ[ƒh‚Ì‰æ‘œ‚Å‚ ‚ê‚Î
		int res = LoadDivGraph(FileName, splitId, splitX, splitY, SizeX / splitX, SizeY / splitY, DivImg[DivImgCounter]);
		if (res == -1) {
			DrawFormatString(0, 70, GetColor(255, 0, 0), _T("y‰æ‘œ“Ç‚İ‚İ‚É¸”s‚µ‚Ü‚µ‚½z%s"), FileName); // •¶š‚ğ•`‰æ‚·‚é
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
