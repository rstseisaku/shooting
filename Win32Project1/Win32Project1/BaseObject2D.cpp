#include "stdafx.h"
#include "BaseObject2D.h"


BaseObject2D::BaseObject2D()
{
}

BaseObject2D::~BaseObject2D()
{
}

void BaseObject2D::InitCommon(const TCHAR *FileName) {
	GraphicHandle = _gl_mGraphicObject->MyLoadGraphic(FileName);
	GetGraphSize(GraphicHandle, &WidthX, &HeightY);
}

void BaseObject2D::MoveFromAngle() {
	Angle = fmod(Angle, 360);
	if (Angle < 0) Angle += 360;

	CenterX += cos(Angle / 180 * M_PI) * Speed;
	CenterY += sin(Angle / 180 * M_PI) * Speed;

	Angle += vAngle;
	vAngle *= vAngleRate;

	if (CenterX < MoveableAreaLeft - 100) ObjectDeleteFlag = true;
	if (CenterY < MoveableAreaUpper - 100 ) ObjectDeleteFlag = true;
	if (CenterX > MoveableAreaRight + 100) ObjectDeleteFlag = true;
	if (CenterY > MoveableAreaButtom + 100) ObjectDeleteFlag = true;
}

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


// フェードアウトの判定・処理
// フェードアウトが始まっていたら処理を行い、trueを返す
bool BaseObject2D::MyFadeout() {
	if (Fadeout >= 0) {
		if (vTransparency == -1) vTransparency = Transparency / Fadeout;
		Transparency -= vTransparency;
		if (Transparency < 0) ObjectDelete();
		return true;
	}
	return false;
}
