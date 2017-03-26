#pragma once
#include "BaseObject.h"

// �����̃I�u�W�F�N�g�̎q�I�u�W�F�N�g�Ƃ��ė��p����
class AnimationObject :
	public BaseObject
{
public:
	AnimationObject(const TCHAR * FileName, int _SplitX, int _SplitY, int _CenterX, int _CenterY);
	~AnimationObject();

	// ��������
	void MyUpdate();
	void MyDraw();
	void MyPeculiarAction(BaseObject * obj);

	void SetParameter( int _AnimationInterval, int _AnimationStart, int _AnimationEND);

	// �摜��12�ɕ����Ǎ�
	int GraphicHandle[100]; // �R���X�g���N�^�Œ�`
	int GraphicPattern; // ���ݕ\�����Ă���O���t�B�b�N�̃p�^�[��ID
	int AnimationInterval = 10; // �A�j���[�V�����̐i�s�p�x
	int AnimationCounter = 0;  // �A�j���[�V�����̐ؑփJ�E���g�ϐ�
	int SplitX; // ��������
	int SplitY; // �c������
	int AnimationStart; // �A�j���[�V�����J�nID
	int AnimationEnd; // �A�j���[�V�����I��ID
	int Transparency; // ���ߓx
	int Mode; // �A���t�@�u�����h�l
};

