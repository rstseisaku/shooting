#include "stdafx.h"

PlayerObject::PlayerObject( const TCHAR *FileName )
{
	// C++ ‚¾‚ÆC‚»‚ñ‚ÈŽè’i‚È‚¢‚Á‚Û‚¢
	InitCommon(FileName);
}

PlayerObject::PlayerObject(const TCHAR *FileName, int _CenterX,int _CenterY)
{
	// C++ ‚¾‚ÆC‚»‚ñ‚ÈŽè’i‚È‚¢‚Á‚Û‚¢
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
	RemainingPlayer = 3;

	Layer = Layer_PlayerObject;
}

void PlayerObject::MyUpdate() 
{
	int Speed = 5;
	// Speed = +GetRand(15);
	if (_gl_KeyControlObject->Key[KEY_INPUT_LSHIFT] >= 1) Speed /= 3;
	if (_gl_KeyControlObject->Key[KEY_INPUT_RIGHT] >= 1) CenterX += Speed;
	if (_gl_KeyControlObject->Key[KEY_INPUT_LEFT] >= 1) CenterX -= Speed;
	if (_gl_KeyControlObject->Key[KEY_INPUT_DOWN] >= 1) CenterY+= Speed;
	if (_gl_KeyControlObject->Key[KEY_INPUT_UP] >= 1) CenterY -= Speed;
}

void PlayerObject::MyDraw()
{
	// DrawFormatString(LeftX, UpperY, GetColor(0, 255, 255), _T("handle %d (%.0f, %.0f)"), GraphicHandle[0], LeftX, UpperY ); // •¶Žš‚ð•`‰æ‚·‚é
	DrawGraph((int)GetDrawX(), (int)GetDrawY(), GraphicHandle[GraphicPattern], true);
	if (++AnimationCounter == AnimationInterval) {
		if (++AnimationCounter == 12) {
			AnimationCounter = 10;
		}
		AnimationCounter = 0;
	}

	DrawFormatString(120, 179, GetColor(0, 255, 255), _T("x,y = %f,%f"), CenterX, CenterY); // •¶Žš‚ð•`‰æ‚·‚é
}

void PlayerObject::MyPeculiarAction(BaseObject * obj) {
	// “Á‚É‚â‚é‚±‚Æ‚Í‚È‚¢
}