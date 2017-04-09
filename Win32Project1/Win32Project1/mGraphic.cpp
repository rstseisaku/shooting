#include "stdafx.h"
#include "mGraphic.h"


/*
* �ǂݍ��񂾉摜���Ǘ�����N���X
*  _gl_mGraphicObject �Ƃ������O�̃O���[�o���ϐ��Ƃ��Ď��̉����Ă����B
* �����摜��ǂݍ��݂ɗ�����A�ȑO�ǂݍ��񂾃n���h����n���B
* (�L���b�V���̂悤�Ȗ������ʂ���)
*/
mGraphic::mGraphic()
{
}


mGraphic::~mGraphic()
{
}

// 1���̉摜��ǂݍ���
int mGraphic::MyLoadGraphic(const TCHAR* FileName)
{
	int GraphicHandle;

	// FileName �Ƃ����摜��ǂݍ��񂾂��Ƃ����邩�ۂ����`�F�b�N����
	int res = (int)GraphicHandleObject.count(FileName);
	if ( res == 0) {
			// �����[�h�̉摜�ł���Ή摜�̓ǂݍ���
			GraphicHandle = LoadGraph(FileName, 0);		if (GraphicHandle == -1) {
			DrawFormatString(0, 70, GetColor(255, 0, 0), _T("�y�摜�ǂݍ��݂Ɏ��s���܂����z%s"), FileName); // ������`�悷��
			ScreenFlip();
			WaitKey();
		}
		GraphicHandleObject[FileName] = GraphicHandle;
	} else {
		// ���[�h�ω摜�ł���΁A�O���t�B�b�N�n���h�����g���܂킷
		GraphicHandle = GraphicHandleObject[FileName];
	}
	return GraphicHandle;
}

void mGraphic::MyLoadDivGraphic(const TCHAR* FileName, int splitX, int splitY, int GraphicHandle[100])
{
	// �摜�̕����ǂݍ���
	// �摜�t�@�C���p�X�E��������������v���Ă���΁A�O���t�B�b�N�n���h�����g���܂킷
	int splitId = splitX * splitY;
	int SizeX, SizeY;
	GetImageSize_File(FileName, &SizeX, &SizeY);
	TCHAR FileNameSplitId[200];
	wsprintf(FileNameSplitId, _T("%s_%d"),FileName,splitId);

	// FileName,SplitId �ɑΉ����镪���摜��ǂݍ��񂾂��Ƃ����邩�ۂ����`�F�b�N����
	int res = (int)DivGraphicHandleObject.count(FileNameSplitId);
	if ( res == 0) { 
		// �����[�h�̉摜�ł���Ή摜�̓ǂݍ���
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
		// ���[�h�ω摜�ł���΁A�O���t�B�b�N�n���h�����g���܂킷
		int tmp = DivGraphicHandleObject[FileNameSplitId];
		for (int i = 0; i < 100; i++) {
			GraphicHandle[i] = DivImg[tmp][i];
		}
	}
}

void mGraphic::MyInitGraph()
{
	// 	�ǂ݂��񂾃O���t�B�b�N�f�[�^�����ׂč폜
	InitGraph();

	// �摜�Ǘ������o�̏�����
	GraphicHandleObject.clear();
	DivGraphicHandleObject.clear();
	DivImgCounter = 0;
}

void mGraphic::MyDeleteGraph(const TCHAR* FileName) 
{
	int res = (int)GraphicHandleObject.count(FileName);
	if (res == 0) {	return; } // �����[�h�̉摜�ł���Ώ������I��
	else 
	{
		// �������J��
		int GraphicHandle;
		GraphicHandle = GraphicHandleObject[FileName];
		DeleteGraph( GraphicHandle );

		//  �摜�Ǘ������o����v�f����菜��
		auto itr = GraphicHandleObject.find(FileName);
		if (itr != GraphicHandleObject.end())         // �L�[�̗v�f�����݂��Ă���ꍇ
			GraphicHandleObject.erase(itr);
	}
}
