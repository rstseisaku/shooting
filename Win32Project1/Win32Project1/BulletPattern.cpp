#include "stdafx.h"
#include "BulletPattern.h"


BulletPattern::BulletPattern()
{
	N = 1; // Nway弾の設定
	Angle = 0; // 起点となる角度
	vAngle = 0; // Angleを毎フレーム変化させる
	vAngleRate = 0.99; // vAngleに毎フレームかける値
	Span = 0; // Nway弾の間隔
	Speed = 30; // 弾のスピード
	X = FieldCenterX; // 射出位置
	Y = FieldCenterY; // 射出位置
	Transparency = 255; // 透過度
	CompositeModeParameter = (int)NORMAL; // 合成モードの設定

	FileName = _T("Image/bullet1.png"); // 画像ファイル名の設定
}


BulletPattern::~BulletPattern()
{
}
