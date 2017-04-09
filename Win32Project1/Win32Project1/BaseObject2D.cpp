#include "stdafx.h"
#include "BaseObject2D.h"


/*
* 画像オブジェクトを設定するためのクラス
* (１枚の画像を持つオブジェクトは、基本的にこのクラスを継承する) 
*/
BaseObject2D::BaseObject2D()
{
}

BaseObject2D::~BaseObject2D()
{
}

void BaseObject2D::InitCommon(const TCHAR *FileName) {
	// グラフィックハンドルとサイズの設定
	GraphicHandle = _gl_mGraphicObject->MyLoadGraphic(FileName);
	GetGraphSize(GraphicHandle, &WidthX, &HeightY);
}

// 現在の角度・スピードをもとに移動する関数
// (Angle vAngle vAngleRate Speed のパラメータを利用する)
void BaseObject2D::MoveFromAngle() {
	// 角度を 0-360 に設定
	Angle = fmod(Angle, 360);
	if (Angle < 0) Angle += 360;

	// Angle・Speed をもとに座標を移動させる
	CenterX += cos(Angle / 180 * M_PI) * Speed;
	CenterY += sin(Angle / 180 * M_PI) * Speed;

	// vAngle・vAngleRate にしたがって、 Angle を更新する
	Angle += vAngle;
	vAngle *= vAngleRate;

	// 場外に逝ったオブジェクトを削除
	if (CenterX < MoveableAreaLeft - 100) ObjectDeleteFlag = true;
	if (CenterY < MoveableAreaUpper - 100 ) ObjectDeleteFlag = true;
	if (CenterX > MoveableAreaRight + 100) ObjectDeleteFlag = true;
	if (CenterY > MoveableAreaButtom + 100) ObjectDeleteFlag = true;
}

// 場外に行きそうなオブジェクトを反射させる関数
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
// ( フェードアウトが始まっていたら処理を行い、trueを返す )
bool BaseObject2D::MyFadeout() {
	if (Fadeout >= 0) {
		if (vTransparency == -1) vTransparency = Transparency / Fadeout;
		Transparency -= vTransparency;
		if (Transparency < 0) ObjectDelete();
		return true;
	}
	return false;
}
