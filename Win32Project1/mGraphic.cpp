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
	if ( res == 0) { // �����[�h�̉摜�ł����
			GraphicHandle = LoadGraph(FileName, 0);		if (GraphicHandle == -1) {
			DrawFormatString(0, 70, GetColor(255, 0, 0), _T("�y�摜�ǂݍ��݂Ɏ��s���܂����z%s"), FileName); // ������`�悷��
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
	if ( res == 0) { // �����[�h�̉摜�ł����
		int res = LoadDivGraph(FileName, splitId, splitX, splitY, SizeX / splitX, SizeY / splitY, DivImg[DivImgCounter]);
		if (res == -1) {
			DrawFormatString(0, 70, GetColor(255, 0, 0), _T("�y�摜�ǂݍ��݂Ɏ��s���܂����z%s"), FileName); // ������`�悷��
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
