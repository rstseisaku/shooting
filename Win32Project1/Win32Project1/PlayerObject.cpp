#include "stdafx.h"

PlayerObject::PlayerObject( const TCHAR *FileName )
{
	// C++ だと，そんな手段ないっぽい
	InitCommon(FileName);
}

PlayerObject::PlayerObject(const TCHAR *FileName, int _CenterX,int _CenterY)
{
	// C++ だと，そんな手段ないっぽい
	InitCommon(FileName);

	CenterX = _CenterX;
	CenterY = _CenterY;
}

PlayerObject::~PlayerObject()
{
}


void PlayerObject::InitCommon(const TCHAR *FileName) {
	int splitX = 3;
	int splitY = 4;
	_gl_mGraphicObject->MyLoadDivGraphic(FileName, splitX, splitY, GraphicHandle);
	GraphicPattern = 10;

	GetGraphSize(GraphicHandle[0], &WidthX, &HeightY);
	Life = 3;
	InvincibleTime = 0;

	Layer = Layer_PlayerObject;
}

void PlayerObject::MyUpdate() 
{
	int Speed = 5;
	if (_gl_KeyControlObject->Key[KEY_INPUT_LSHIFT] >= 1) Speed /= 3;
	if (_gl_KeyControlObject->Key[KEY_INPUT_RIGHT] >= 1) CenterX += Speed;
	if (_gl_KeyControlObject->Key[KEY_INPUT_LEFT] >= 1) CenterX -= Speed;
	if (_gl_KeyControlObject->Key[KEY_INPUT_DOWN] >= 1) CenterY+= Speed;
	if (_gl_KeyControlObject->Key[KEY_INPUT_UP] >= 1) CenterY -= Speed;

	if (CenterX <= 35)  CenterX = 35;
	if (CenterY <= 35)  CenterY = 35;
	if (CenterX >= 540 )  CenterX = 540;
	if (CenterY >= WindowSizeY - 35)  CenterY = WindowSizeY - 35;
}

void PlayerObject::MyDraw()
{
	SetDrawBlendMode(NORMAL, 255);
	if (InvincibleTime > 0) 
	{
		InvincibleTime--;
		if (InvincibleTime > 60) {
			SetDrawBlendMode(NORMAL, 127);
		}
	}
	DrawGraph((int)GetDrawX(), (int)GetDrawY(), GraphicHandle[GraphicPattern], true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

	if (++AnimationCounter == AnimationInterval) {
		if (++AnimationCounter == 12) {
			AnimationCounter = 10;
		}
		AnimationCounter = 0;
	}

	if( DEBUG )
		DrawFormatString(120, 179, GetColor(0, 255, 255), _T("x,y = %f,%f"), CenterX, CenterY); // 文字を描画する
}

void PlayerObject::MyPeculiarAction(BaseObject * obj) {
	// 特にやることはない
}