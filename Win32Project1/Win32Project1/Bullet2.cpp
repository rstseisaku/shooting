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
	Angle = _Angle;
	Speed = _Speed;
}

Bullet2::Bullet2(const TCHAR * FileName, int _x, int _y, int _Angle, int _Speed)
{
	InitCommon(FileName); // 画像ハンドル WidthX HeightYの算出
	Angle = _Angle;
	Speed = _Speed / 60;
	CenterX = _x;
	CenterY = _y;
}

Bullet2::~Bullet2()
{
}

void Bullet2::MyUpdate() {	
	CenterX += cos(Angle) * Speed;
	CenterY += sin(Angle) * Speed;
	Angle += M_PI / 360;
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
	DrawRotaGraph((int)CenterX , (int)CenterY, 1.0,  Angle,
		GraphicHandle, true);
}

void Bullet2::MyPeculiarAction(BaseObject * obj)
{
}
