#pragma once
#include "BaseObject.h"

// 何かのオブジェクトの子オブジェクトとして利用する
class AnimationObject :
	public BaseObject
{
public:
	AnimationObject(const TCHAR * FileName, int _SplitX, int _SplitY, int _CenterX, int _CenterY);
	~AnimationObject();

	// 実装する
	void MyUpdate();
	void MyDraw();
	void MyPeculiarAction(BaseObject * obj);

	void SetParameter( int _AnimationInterval, int _AnimationStart, int _AnimationEND);

	// 画像を12個に分割読込
	int GraphicHandle[100]; // コンストラクタで定義
	int GraphicPattern; // 現在表示しているグラフィックのパターンID
	int AnimationInterval = 10; // アニメーションの進行頻度
	int AnimationCounter = 0;  // アニメーションの切替カウント変数
	int SplitX; // 横分割数
	int SplitY; // 縦分割数
	int AnimationStart; // アニメーション開始ID
	int AnimationEnd; // アニメーション終了ID
	int Transparency; // 透過度
	int Mode; // アルファブレンド値
};

