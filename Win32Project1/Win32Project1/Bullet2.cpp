#include "stdafx.h"
#include "Bullet2.h"


Bullet2::Bullet2()
{
}

Bullet2::Bullet2(const TCHAR * FileName)
{
	InitCommon(FileName); // 画像ハンドル WidthX HeightYの算出
}

Bullet2::Bullet2(const TCHAR * FileName, int _Angle, int _Speed)
{
	InitCommon(FileName); // 画像ハンドル WidthX HeightYの算出
	Angle = _Angle % 360;
	Speed = _Speed / 60.0;
}

Bullet2::Bullet2(const TCHAR * FileName, int _x, int _y, int _Angle, int _Speed)
{
	InitCommon(FileName); // 画像ハンドル WidthX HeightYの算出
	Angle = _Angle % 360;
	Speed = _Speed / 60.0;
	CenterX = _x;
	CenterY = _y;
}

Bullet2::Bullet2(const TCHAR * FileName, int _x, int _y, int _Angle, int _Speed, 
				 int _Mode, int _Transparency )
{
	InitCommon(FileName); // 画像ハンドル WidthX HeightYの算出
	Angle = _Angle % 360;
	Speed = _Speed / 60.0;
	CenterX = _x;
	CenterY = _y;
	Mode = _Mode;
	Transparency = _Transparency;
}

Bullet2::~Bullet2()
{
	MyDestructor();
}

void Bullet2::MyUpdate() {
	if (MyFadeout()) return; // フェードアウトの判定・処理
	MoveFromAngle();
}

void Bullet2::MyDraw() {
	/*
	宣言	int DrawRotaGraph(int x, int y, double ExtRate, double Angle,
		int GrHandle, int TransFlag);

	概略	メモリに読みこんだグラフィックの回転描画

		引数	x, y　　　: グラフィックを描画する領域の中心座標
		ExtRate　　 : 拡大率（１.０で等倍）
		Angle　　　 : 描画角度（ラジアン指定）
		GrHandle　 : 描画するグラフィックの識別番号（グラフィックハンドル）
		TransFlag　 : 透過色が有効か、フラグ（TRUEで有効FALSEで無効）
	*/

	/*
	//乗算済みアルファ用のアルファブレンド
    DX_BLENDMODE_PMA_ALPHA

    // 乗算済みアルファ用の加算ブレンド
    DX_BLENDMODE_PMA_ADD

    // 乗算済みアルファ用の減算ブレンド
    DX_BLENDMODE_PMA_SUB
	*/

	SetDrawBlendMode(Mode, Transparency);
	DrawRotaGraph((int)CenterX , (int)CenterY, 1.0, Angle / 180 * M_PI,
		GraphicHandle, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);


	//DrawFormatString(100, 400, GetColor(0, 255, 255), _T("angle %f"), Angle); // 文字を描画する
}

void Bullet2::MyPeculiarAction(BaseObject * obj)
{
}
