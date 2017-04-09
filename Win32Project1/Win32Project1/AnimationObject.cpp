#include "stdafx.h"
#include "AnimationObject.h"


AnimationObject::AnimationObject(const TCHAR * FileName, int _SplitX, int _SplitY, int _CenterX, int _CenterY)
{
	// �R���X�g���N�^�Ńp�����[�^�̐ݒ�
	SplitX = _SplitX; // ��������
	SplitY = _SplitY; // �c������
	CenterX = _CenterX; // �������WX
	CenterY = _CenterY; // �������WY
	_gl_mGraphicObject->MyLoadDivGraphic(FileName, SplitX, SplitY, GraphicHandle); // �摜�����ǂݍ���
	GetGraphSize(GraphicHandle[0], &WidthX, &HeightY); // �摜�T�C�Y�̎擾
	Mode = NORMAL; // �A���t�@�u�����h�̐ݒ�
	Transparency = 255; // ���ߓx255�ɐݒ�
	Enlargement = 1.0; // �g�嗦��1.0�ɐݒ�
	GraphicPattern = 0; // �O���t�B�b�N�\���p�^�[����0�ɃZ�b�g
}

AnimationObject::~AnimationObject()
{
}

void AnimationObject::MyUpdate()
{
	// �A�j���[�V������i�߂�
	AnimationCounter = (++AnimationCounter) % AnimationInterval;
	if (AnimationCounter == 0) {
		GraphicPattern++;
		// �A�j���[�V�������I��������A�I�u�W�F�N�g���폜
		if (GraphicPattern == (AnimationEnd + 1))  ObjectDelete();
	}
}

void AnimationObject::MyDraw()
{
	// �I�u�W�F�N�g�̉摜��\��
	SetDrawBlendMode(Mode, Transparency);
	DrawRotaGraph((int)CenterX, (int)CenterY, Enlargement, 0,
		GraphicHandle[GraphicPattern], true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
}

void AnimationObject::MyPeculiarAction(BaseObject * obj)
{
	// ���ɕK�v�Ȃ�
}

void AnimationObject::SetParameter(int _AnimationInterval, int _AnimationStart, int _AnimationEND)
{
	// �p�����[�^�̐ݒ�
	AnimationInterval = _AnimationInterval; // �A�j���[�V�����̊Ԋu
	AnimationStart = _AnimationStart; // �A�j���[�V�����̃X�^�[�g�t�ʒu
	AnimationEnd = _AnimationEND; // �A�j���[�V�����̏I���ʒu

	GraphicPattern = AnimationStart; // �O���t�B�b�N�\���p�^�[�����J�n�ʒu�ɃZ�b�g
}
