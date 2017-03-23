#include "stdafx.h"
#include "BaseObject2D.h"


BaseObject2D::BaseObject2D()
{
}


BaseObject2D::~BaseObject2D()
{
}


// 「全てのオブジェクトが画像を持つ」と設計すれば、
// この処理は「ベースオブジェクト」に移せる
void BaseObject2D::InitCommon(const TCHAR *FileName) {
	GraphicHandle = _gl_mGraphicObject->MyLoadGraphic(FileName);
	GetGraphSize(GraphicHandle, &WidthX, &HeightY);
}
