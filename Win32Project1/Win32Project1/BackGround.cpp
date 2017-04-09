#include "stdafx.h"
#include "BackGround.h"


BackGround::BackGround()
{
}

BackGround::BackGround(const TCHAR * FileName, int _CenterX, int _CenterY)
{
	// ����������
	InitCommon(FileName); // �t�@�C��������O���t�B�b�N�n���h���E�T�C�Y���擾
	CenterX = _CenterX;
	CenterY = _CenterY;
	LoopPoint = _CenterY; // ���[�v�ʒu�̐ݒ�

	Layer = Layer_BackGround; // ���C���̐ݒ�
}

BackGround::~BackGround()
{
}

void BackGround::MyUpdate()
{
	// �������ɃX�N���[��������
	CenterY += 1;
	if (CenterY >= LoopPoint) {
		// ���ʒu�Ń��[�v������
		CenterY = 0;
	}
}

void BackGround::MyDraw() {
	// �I�u�W�F�N�g�̉摜��\��
	DrawGraph((int)GetDrawX(), (int)GetDrawY(), GraphicHandle, true);
}

void BackGround::MyPeculiarAction(BaseObject * obj) {
	// ���ɂ�邱�Ƃ͂Ȃ�
}