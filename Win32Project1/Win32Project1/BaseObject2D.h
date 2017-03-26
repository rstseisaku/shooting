#pragma once
#include "BaseObject.h"
class BaseObject2D :
	public BaseObject
{
public:
	BaseObject2D();
	~BaseObject2D();

	void InitCommon(const TCHAR * FileName);
	void MoveFromAngle();
	void Reflect();

	bool MyFadeout();

	int GraphicHandle; // 画像データのハンドル
	double Angle = 0;
	double vAngle = 0; // 毎フレーム Angle に加算する
	double vAngleRate = 0.99; // 毎フレーム vAngle に掛け算する(vAngleを0に収束させる)
	double Speed = 0;
	int Transparency = 255; // 透過度0をデフォルトとする
	int Mode = DX_BLENDMODE_PMA_ALPHA; // 通常描画をデフォルト

	bool GrazeFlag = false; // グレイズしたら true を代入
	bool NoHitFlag = false; // 当たり判定消去中
	int Fadeout = -1; // フェードアウトのフレームを算出
	int vTransparency = -1; // 透過度変化

	double GrazeScore; // かすった時に加算されるスコア
	double EraseScore; // ボムで消える時に加算されるスコア
};

