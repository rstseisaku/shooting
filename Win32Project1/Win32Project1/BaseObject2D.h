#pragma once
#include "BaseObject.h"
class BaseObject2D :
	public BaseObject
{
public:
	BaseObject2D();
	~BaseObject2D();

	void InitCommon(const TCHAR * FileName);
	void MoveFromAngle();
	void Reflect();

	bool MyFadeout();

	int GraphicHandle; // �摜�f�[�^�̃n���h��
	double Angle = 0;
	double vAngle = 0; // ���t���[�� Angle �ɉ��Z����
	double vAngleRate = 0.99; // ���t���[�� vAngle �Ɋ|���Z����(vAngle��0�Ɏ���������)
	double Speed = 0;
	int Transparency = 255; // ���ߓx0���f�t�H���g�Ƃ���
	int Mode = DX_BLENDMODE_PMA_ALPHA; // �ʏ�`����f�t�H���g

	bool GrazeFlag = false; // �O���C�Y������ true ����
	bool NoHitFlag = false; // �����蔻�������
	int Fadeout = -1; // �t�F�[�h�A�E�g�̃t���[�����Z�o
	int vTransparency = -1; // ���ߓx�ω�

	double GrazeScore; // �����������ɉ��Z�����X�R�A
	double EraseScore; // �{���ŏ����鎞�ɉ��Z�����X�R�A
};

