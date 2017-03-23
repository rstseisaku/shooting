#pragma once
#include "BaseObject.h"
class BaseObject2D :
	public BaseObject
{
public:
	BaseObject2D();
	~BaseObject2D();
	void InitCommon(const TCHAR * FileName);

	int GraphicHandle; // �摜�f�[�^�̃n���h��
	double Angle = 0;
	double vAngle = 0;
	int Transparency = 255; // ���ߓx0���f�t�H���g�Ƃ���
	int Mode = DX_BLENDMODE_PMA_ALPHA; // �ʏ�`����f�t�H���g
};

