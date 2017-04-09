#include "stdafx.h"
#include "ItemObject.h"


ItemObject::ItemObject(const TCHAR * FileName, int _CenterX, int _CenterY, int _Layer)
{
	// ����������
	InitCommon(FileName); // �t�@�C��������O���t�B�b�N�n���h���E�T�C�Y���擾
	CenterX = _CenterX;
	CenterY = _CenterY;
	Layer = _Layer; // �A�C�e���I�u�W�F�N�g�́A���C���[�𗘗p���ăA�C�e����ނ𔻒f
}

ItemObject::~ItemObject()
{
	// �q�I�u�W�F�N�g�̏���
	MyDestructor();
}

void ItemObject::MyUpdate()
{
	// �A�C�e���I�u�W�F�N�g�͂Ƃ���̂�҂���( �������Ȃ� )
}

void ItemObject::MyDraw()
{
	// �I�u�W�F�N�g�̉摜��\��
	SetDrawBlendMode(Mode, Transparency);
	DrawRotaGraph((int)CenterX, (int)CenterY, 1.0, Angle / 180 * M_PI,
		GraphicHandle, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
}

void ItemObject::MyPeculiarAction(BaseObject * obj)
{
	// �󂯎��I�u�W�F�N�g���v���C���I�u�W�F�N�g���m�F
	if (obj->Layer != Layer_PlayerObject) return;

	// �󂯎�����v���C���I�u�W�F�N�g����l���擾
	double PlayerX = obj->CenterX;
	double PlayerY = obj->CenterY;

	// �v���C���ƃA�C�e���̋������Z�o
	double DistX = abs(PlayerX - CenterX);
	double DistY = abs(PlayerY - CenterY);

	// ��`����
	if (DistX <= (WidthX / 2) && DistY <= (HeightY / 2)) {
		// ���C���ɉ����āA�A�C�e���l������
		if (Layer == Layer_Item) ((PlayerObject*)obj)->GetItemNum++;
		if (Layer == Layer_RareItem) ((PlayerObject*)obj)->GetRareItemNum++;
		if (Layer == Layer_BomItem) ((PlayerObject*)obj)->BomSize += 50;

		// �A�C�e���擾�G�t�F�N�g�\��
		AnimationObject *AnimationObjectTmp;
		AnimationObjectTmp = new AnimationObject(
			_T("Image/Animation3.png"),
			10,
			1,
			((PlayerObject*)obj)->CenterX,
			((PlayerObject*)obj)->CenterY);
		AnimationObjectTmp->Mode = ADD; // �A���t�@�u�����h�����Z�\���ɐݒ�
		AnimationObjectTmp->SetParameter(2, 0, 9); // �A�j���[�V�����p�x�E�J�n�E�I�����Z�b�g

	    // �v���C���I�u�W�F�N�g�̎q�I�u�W�F�N�g�Ƃ��āA�A�j���[�V�����I�u�W�F�N�g��o�^
		((PlayerObject*)obj)->AddObject(AnimationObjectTmp); 

		// �擾���Đ�
		_gl_mSoundObject->MyPlaySoundMem(_T("Sound/on11.wav"), DX_PLAYTYPE_BACK);

		// �����t���O�𗧂Ă�
		ObjectDelete();
	}
}
