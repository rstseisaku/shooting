#include "stdafx.h"
#include "Bullet2.h"


Bullet2::Bullet2()
{
}

Bullet2::Bullet2(const TCHAR * FileName)
{
	// 初期化処理
	InitCommon(FileName); // ファイル名からグラフィックハンドル・サイズを取得
}

Bullet2::Bullet2(const TCHAR * FileName, int _Angle, int _Speed)
{
	// 初期化処理
	InitCommon(FileName); // ファイル名からグラフィックハンドル・サイズを取得
	Angle = _Angle % 360; // 0-360に収める
	Speed = _Speed / 60.0; // 1秒間に移動する値を、1フレームあたりの値に変換する
}

Bullet2::Bullet2(const TCHAR * FileName, int _x, int _y, int _Angle, int _Speed)
{
	// 初期化処理
	InitCommon(FileName); // ファイル名からグラフィックハンドル・サイズを取得
	Angle = _Angle % 360; // 0-360に収める
	Speed = _Speed / 60.0; // 1秒間に移動する値を、1フレームあたりの値に変換する
	CenterX = _x;
	CenterY = _y;
}

Bullet2::Bullet2(const TCHAR * FileName, int _x, int _y, int _Angle, int _Speed, 
				 int _Mode, int _Transparency )
{
	// 初期化処理
	InitCommon(FileName); // ファイル名からグラフィックハンドル・サイズを取得
	Angle = _Angle % 360; // 0-360に収める
	Speed = _Speed / 60.0; // 1秒間に移動する値を、1フレームあたりの値に変換する
	CenterX = _x;
	CenterY = _y;
	Mode = _Mode; // アルファブレンド値
	Transparency = _Transparency; // 透過度の設定
}

Bullet2::~Bullet2()
{
	// 子オブジェクトの消去
	MyDestructor();
}

void Bullet2::MyUpdate() {
	// フェードアウトが始まっていたら、処理を停止する
	if (MyFadeout()) return;

	// 現在の角度・スピードをもとに移動する関数( Speed，Angle, vAngle, vAngleRate )
	MoveFromAngle();
}

void Bullet2::MyDraw() {
	// オブジェクトの画像を表示
	SetDrawBlendMode(Mode, Transparency);
	DrawRotaGraph((int)CenterX , (int)CenterY, 1.0, Angle / 180 * M_PI,
		GraphicHandle, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
}

void Bullet2::MyPeculiarAction(BaseObject * obj)
{
	// 特にやることはない
}
