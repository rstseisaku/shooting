#include "stdafx.h"
#include "BaseObject2D.h"


/*
* �摜�I�u�W�F�N�g��ݒ肷�邽�߂̃N���X
* (�P���̉摜�����I�u�W�F�N�g�́A��{�I�ɂ��̃N���X���p������) 
*/
BaseObject2D::BaseObject2D()
{
}

BaseObject2D::~BaseObject2D()
{
}

void BaseObject2D::InitCommon(const TCHAR *FileName) {
	// �O���t�B�b�N�n���h���ƃT�C�Y�̐ݒ�
	GraphicHandle = _gl_mGraphicObject->MyLoadGraphic(FileName);
	GetGraphSize(GraphicHandle, &WidthX, &HeightY);
}

// ���݂̊p�x�E�X�s�[�h�����ƂɈړ�����֐�
// (Angle vAngle vAngleRate Speed �̃p�����[�^�𗘗p����)
void BaseObject2D::MoveFromAngle() {
	// �p�x�� 0-360 �ɐݒ�
	Angle = fmod(Angle, 360);
	if (Angle < 0) Angle += 360;

	// Angle�ESpeed �����Ƃɍ��W���ړ�������
	CenterX += cos(Angle / 180 * M_PI) * Speed;
	CenterY += sin(Angle / 180 * M_PI) * Speed;

	// vAngle�EvAngleRate �ɂ��������āA Angle ���X�V����
	Angle += vAngle;
	vAngle *= vAngleRate;

	// ��O�ɐ������I�u�W�F�N�g���폜
	if (CenterX < MoveableAreaLeft - 100) ObjectDeleteFlag = true;
	if (CenterY < MoveableAreaUpper - 100 ) ObjectDeleteFlag = true;
	if (CenterX > MoveableAreaRight + 100) ObjectDeleteFlag = true;
	if (CenterY > MoveableAreaButtom + 100) ObjectDeleteFlag = true;
}

// ��O�ɍs�������ȃI�u�W�F�N�g�𔽎˂�����֐�
void BaseObject2D::Reflect() {
	if (CenterY <= MoveableAreaUpper)
	{
		Angle *= -1;
	}
	else if (CenterY >= MoveableAreaButtom)
	{
		Angle += 180;
		Angle *= -1;
		Angle += 180;
	}

	if (CenterX <= MoveableAreaLeft && (Angle > 90 && Angle < 270))
	{
		Angle -= 90;
		Angle *= -1;
		Angle += 90;
	}
	else if (CenterX >= MoveableAreaRight && (Angle < 90 || Angle > 270))
	{
		Angle += 90;
		Angle *= -1;
		Angle -= 90;
	}
}


// �t�F�[�h�A�E�g�̔���E����
// ( �t�F�[�h�A�E�g���n�܂��Ă����珈�����s���Atrue��Ԃ� )
bool BaseObject2D::MyFadeout() {
	if (Fadeout >= 0) {
		if (vTransparency == -1) vTransparency = Transparency / Fadeout;
		Transparency -= vTransparency;
		if (Transparency < 0) ObjectDelete();
		return true;
	}
	return false;
}
