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

// 「全てのオブジェクトが画像を持つ」と設計すれば、
// この処理は「ベースオブジェクト」に移せる
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
	// プレイヤーオブジェクトの座標をコピーする
	CenterX = obj->CenterX;
	CenterY = obj->CenterY;
}

void PlayerDecorationObject::MyUpdate()
{
}
