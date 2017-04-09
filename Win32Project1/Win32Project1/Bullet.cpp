#include "stdafx.h"


Bullet::Bullet()
{
}


Bullet::Bullet(const TCHAR * FileName)
{
	// 初期化処理
	InitCommon(FileName); // ファイル名からグラフィックハンドル・サイズを取得
}

Bullet::Bullet(const TCHAR * FileName, int _CenterX, int _CenterY)
{
	// 初期化処理
	InitCommon(FileName); // ファイル名からグラフィックハンドル・サイズを取得
	CenterX = _CenterX;
	CenterY = _CenterY;
}

Bullet::Bullet(const TCHAR * FileName, int _CenterX, int _CenterY, double _vx, double _vy)
{
	// 初期化処理
	InitCommon(FileName); // ファイル名からグラフィックハンドル・サイズを取得
	CenterX = _CenterX;
	CenterY = _CenterY;
	vx = _vx;
	vy = _vy;
}

Bullet::Bullet(const TCHAR * FileName, int _CenterX, int _CenterY,
	double _vx, double _vy, double _vvx, double _vvy)
{
	// 初期化処理
	InitCommon(FileName); // ファイル名からグラフィックハンドル・サイズを取得
	CenterX = _CenterX;
	CenterY = _CenterY;
	vx = _vx;
	vy = _vy;
	vvx = _vvx; // 加速度x
	vvy = _vvy; // 加速度y
}

Bullet::~Bullet()
{
	// 子オブジェクトの消去
	MyDestructor();
}

void Bullet::MyUpdate()
{
	// フェードアウトが始まっていたら、処理を停止する
	if (MyFadeout()) return;

	// 加速度・速度を反映し、移動させる
	vx += vvx;
	vy += vvy;
	CenterX += vx;
	CenterY += vy;

	// 角度の更新
	Angle = atan2(vy, vx);
	Angle = Angle * 180.0 / M_PI;

	// 場外オブジェクト削除
	if (CenterX < MoveableAreaLeft - 100) ObjectDeleteFlag = true;
	if (CenterY < MoveableAreaUpper - 100) ObjectDeleteFlag = true;
	if (CenterX > MoveableAreaRight + 100) ObjectDeleteFlag = true;
	if (CenterY > MoveableAreaButtom + 100) ObjectDeleteFlag = true;
}

void Bullet::MyDraw() {
	// オブジェクトの画像を表示
	SetDrawBlendMode(Mode, Transparency);
	DrawRotaGraph((int)CenterX, (int)CenterY, 1.0, Angle / 180 * M_PI,
		GraphicHandle, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
}

void Bullet::MyPeculiarAction(BaseObject * obj) {
	// 特にやることはない
}
