#include "stdafx.h"
#include "ItemObject.h"


ItemObject::ItemObject(const TCHAR * FileName, int _CenterX, int _CenterY, int _Layer)
{
	InitCommon(FileName);
	CenterX = _CenterX;
	CenterY = _CenterY;
	Layer = _Layer;
}

ItemObject::~ItemObject()
{
}

void ItemObject::MyUpdate()
{
}

void ItemObject::MyDraw()
{
	SetDrawBlendMode(Mode, Transparency);
	DrawRotaGraph((int)CenterX, (int)CenterY, 1.0, Angle / 180 * M_PI,
		GraphicHandle, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
}

void ItemObject::MyPeculiarAction(BaseObject * obj)
{
	// �v���C���I�u�W�F�N�g���󂯎��
	double PlayerX = obj->CenterX;
	double PlayerY = obj->CenterY;
	double DistX = abs(PlayerX - CenterX);
	double DistY = abs(PlayerY - CenterY);

	// ��`����
	if (DistX <= (WidthX / 2) && DistY <= (HeightY / 2)) {
		// �A�C�e���l������
		if (Layer == Layer_Item) ((PlayerObject*)obj)->GetItemNum++;
		if (Layer == Layer_RareItem) ((PlayerObject*)obj)->GetRareItemNum++;
		_gl_mSoundObject->MyPlaySoundMem(_T("Sound/on11.wav"), DX_PLAYTYPE_BACK); // �擾���Đ�
		ObjectDelete();
	}
}
