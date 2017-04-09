#include "stdafx.h"
#include "PlayerDecorationObject.h"


PlayerDecorationObject::PlayerDecorationObject( const TCHAR * FileName )
{
	InitCommon(FileName);
}


PlayerDecorationObject::PlayerDecorationObject()
{
}

PlayerDecorationObject::~PlayerDecorationObject()
{
	MyDestructor();
}

// �u�S�ẴI�u�W�F�N�g���摜�����v�Ɛ݌v����΁A
// ���̏����́u�x�[�X�I�u�W�F�N�g�v�Ɉڂ���
void PlayerDecorationObject::InitCommon(const TCHAR *FileName) {
	GraphicHandle = _gl_mGraphicObject->MyLoadGraphic(FileName);
	GetGraphSize(GraphicHandle, &WidthX, &HeightY);
	Layer = Layer_PlayerDecorationObject;
}

void PlayerDecorationObject::MyDraw()
{
	if (_gl_KeyControlObject->Key[KEY_INPUT_LSHIFT] >= 1)
	DrawGraph((int)GetDrawX(), (int)GetDrawY(), GraphicHandle, true);
}

void PlayerDecorationObject::MyPeculiarAction(BaseObject * obj)
{
	// �v���C���[�I�u�W�F�N�g�̍��W���R�s�[����
	CenterX = obj->CenterX;
	CenterY = obj->CenterY;
}

void PlayerDecorationObject::MyUpdate()
{
}
