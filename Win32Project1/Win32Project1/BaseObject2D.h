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

	int GraphicHandle; // �摜�f�[�^�̃n���h��
	double Angle = 0;
	double vAngle = 0; // ���t���[�� Angle �ɉ��Z����
	double vAngleRate = 0.99; // ���t���[�� vAngle �Ɋ|���Z����(vAngle��0�Ɏ���������)
	double Speed = 0;
	int Transparency = 255; // ���ߓx0���f�t�H���g�Ƃ���
	bool GrazeFlag = false; // �O���C�Y������ true ����
	int Mode = DX_BLENDMODE_PMA_ALPHA; // �ʏ�`����f�t�H���g
};

