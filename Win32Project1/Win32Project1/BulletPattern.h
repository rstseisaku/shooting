#pragma once

// 弾幕パターンのテンプレートを設定するクラス。
class BulletPattern
{
public:
	BulletPattern();
	~BulletPattern();

	int N; // Nway弾の設定
	double Angle; // 起点となる角度
	double Span; // Nway弾の間隔
	double Speed; // 弾のスピード
	double X; // 射出位置
	double Y; // 射出位置
	int Transparency; // 透過度
	int CompositeModeParameter; // 合成モードの設定
	TCHAR * FileName; // 画像ファイル名の設定
};