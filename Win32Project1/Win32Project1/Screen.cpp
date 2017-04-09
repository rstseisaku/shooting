#include "stdafx.h"
#include "Screen.h"


Screen::Screen()
{
}

Screen::Screen(const TCHAR * FileName, int _CenterX, int _CenterY, PlayerObject* Player)
{
	// ����������
	InitCommon(FileName); // �t�@�C��������O���t�B�b�N�n���h���E�T�C�Y���擾
	CenterX = _CenterX;
	CenterY = _CenterY;
	PlayerObj = Player; // �v���C���[�I�u�W�F�N�g�̃C���X�^���X�ێ�

	ScoreFont = CreateFontToHandle(NULL, 64, 3); // �X�R�A�t�H���g�̐ݒ�n���h���̎擾
	LifeGraphic = _gl_mGraphicObject->MyLoadGraphic(_T("Image/life.png")); // ���C�t�摜�ǂݍ���

	Layer = Layer_Screen; // ���C���ݒ�
}

Screen::~Screen()
{
	// �q�I�u�W�F�N�g�̏���
	MyDestructor();
}

void Screen::MyUpdate()
{
	// �e�X�R�A�����Z���Ă���
	TimeScore += 1.0 / 60; // ���Ԍo�߂ɂ��X�R�A�㏸
	GrazeScore = PlayerObj->GrazeScore; // �O���C�Y�X�R�A�ǂݍ���
	EraseScore = PlayerObj->EraseScore; // �{���ɂ��X�R�A�ǂݍ���
}

void Screen::MyDraw() {
	DrawGraph((int)GetDrawX(), (int)GetDrawY(), GraphicHandle, true);

	ShowLife();
	ShowScore();
	//if (DEBUG)
		//DrawFormatString(600, 200, GetColor(0, 255, 255), _T("(Screen)Life %d"), PlayerObj->Life); // ������`�悷��
		//DrawFormatStringToHandle(600, 400, GetColor(0, 0, 0), ScoreFont, _T("%d"), (int)(TimeScore + GrazeScore + EraseScore)); // �X�R�A
		//DrawFormatString(600, 470, GetColor(0, 0, 0), _T("�{��:%d"), (int)PlayerObj->tmp); // �n�C�X�R�A
}

void Screen::MyPeculiarAction(BaseObject * obj) {
	// ���ɂ�邱�Ƃ͂Ȃ�
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
	DrawFormatStringToHandle(960 - ScoreLength, 400, GetColor(0, 0, 0), ScoreFont, _T("%d"), (int)(TimeScore + GrazeScore + EraseScore)); // �X�R�A
	//DrawFormatString(600, 470, GetColor(0, 0, 0), _T("�{��:%d"), (int)PlayerObj->tmp); // �n�C�X�R�A
}