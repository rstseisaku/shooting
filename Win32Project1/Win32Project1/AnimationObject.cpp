#include "stdafx.h"
#include "AnimationObject.h"


AnimationObject::AnimationObject(const TCHAR * FileName, int _SplitX, int _SplitY, int _CenterX, int _CenterY)
{
	// コンストラクタでパラメータの設定
	SplitX = _SplitX; // 横分割数
	SplitY = _SplitY; // 縦分割数
	CenterX = _CenterX; // 中央座標X
	CenterY = _CenterY; // 中央座標Y
	_gl_mGraphicObject->MyLoadDivGraphic(FileName, SplitX, SplitY, GraphicHandle); // 画像分割読み込み
	GetGraphSize(GraphicHandle[0], &WidthX, &HeightY); // 画像サイズの取得
	Mode = NORMAL; // アルファブレンドの設定
	Transparency = 255; // 透過度255に設定
	Enlargement = 1.0; // 拡大率を1.0に設定
	GraphicPattern = 0; // グラフィック表示パターンを0にセット
}

AnimationObject::~AnimationObject()
{
}

void AnimationObject::MyUpdate()
{
	// アニメーションを進める
	AnimationCounter = (++AnimationCounter) % AnimationInterval;
	if (AnimationCounter == 0) {
		GraphicPattern++;
		// アニメーションが終了したら、オブジェクトを削除
		if (GraphicPattern == (AnimationEnd + 1))  ObjectDelete();
	}
}

void AnimationObject::MyDraw()
{
	// オブジェクトの画像を表示
	SetDrawBlendMode(Mode, Transparency);
	DrawRotaGraph((int)CenterX, (int)CenterY, Enlargement, 0,
		GraphicHandle[GraphicPattern], true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
}

void AnimationObject::MyPeculiarAction(BaseObject * obj)
{
	// 特に必要ない
}

void AnimationObject::SetParameter(int _AnimationInterval, int _AnimationStart, int _AnimationEND)
{
	// パラメータの設定
	AnimationInterval = _AnimationInterval; // アニメーションの間隔
	AnimationStart = _AnimationStart; // アニメーションのスタートフ位置
	AnimationEnd = _AnimationEND; // アニメーションの終了位置

	GraphicPattern = AnimationStart; // グラフィック表示パターンを開始位置にセット
}
