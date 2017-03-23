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
}

void Bullet2::MyUpdate() {
	Angle = fmod(Angle,360);
	if (Angle < 0) Angle += 360;

	CenterX += cos( Angle / 180 * M_PI ) * Speed;
	CenterY += sin( Angle / 180 * M_PI ) * Speed;

	Angle += vAngle;
	vAngle *= vAngleRate;


	if (CenterX < -100) ObjectDeleteFlag = true;
	if (CenterY < -100) ObjectDeleteFlag = true;
	if (CenterX > 640) ObjectDeleteFlag = true;
	if (CenterY > WindowSizeY + 65) ObjectDeleteFlag = true;
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

}

void Bullet2::MyPeculiarAction(BaseObject * obj)
{
}
