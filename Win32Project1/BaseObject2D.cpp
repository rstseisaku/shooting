#include "stdafx.h"
#include "BaseObject2D.h"


BaseObject2D::BaseObject2D()
{
}


BaseObject2D::~BaseObject2D()
{
}


// �u�S�ẴI�u�W�F�N�g���摜�����v�Ɛ݌v����΁A
// ���̏����́u�x�[�X�I�u�W�F�N�g�v�Ɉڂ���
void BaseObject2D::InitCommon(const TCHAR *FileName) {
	GraphicHandle = _gl_mGraphicObject->MyLoadGraphic(FileName);
	GetGraphSize(GraphicHandle, &WidthX, &HeightY);
}
