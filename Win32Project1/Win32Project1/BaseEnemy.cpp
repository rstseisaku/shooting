#include "stdafx.h"
#include "BaseEnemy.h"

/*
 * 敵クラスを設定するためのクラス
 * 敵オブジェクトは、このクラスを継承して作成する
 */
BaseEnemy::BaseEnemy(const TCHAR * FileName, mEnemyBullet * obj, PlayerObject * _PlayerObjectInstance)
{
	// 初期化処理
	InitCommon(FileName); // ファイル名からグラフィックハンドル・サイズを取得
	mEnemyBulletObject = obj; // 敵弾管理オブジェクトへのアドレスを格納
	PlayerObjectInstance = _PlayerObjectInstance; // プレイヤークラスへのアドレスを格納

	Pattern = NOSELECTED; // 弾幕パターンを未選択状態に設定
}

BaseEnemy::BaseEnemy(const TCHAR * FileName, mEnemyBullet * obj, PlayerObject * _PlayerObjectInstance, double _X, double _Y)
{
	// 初期化処理
	InitCommon(FileName); // ファイル名からグラフィックハンドル・サイズを取得
	mEnemyBulletObject = obj; // 敵弾管理オブジェクトへのアドレスを格納
	PlayerObjectInstance = _PlayerObjectInstance; // プレイヤークラスへのアドレスを格納
	CenterX = _X;
	CenterY = _Y;

	Pattern = NOSELECTED; // 弾幕パターンを未選択状態に設定
}

BaseEnemy::~BaseEnemy()
{
}

double BaseEnemy::GetAngleToPlayer() {
	// 自機への角度を求める
	double Ans =
		atan2(PlayerObjectInstance->CenterY - CenterY,
			PlayerObjectInstance->CenterX - CenterX);
	Ans = Ans * 180.0 / M_PI; // 度 = ラジアン × 180 ÷ 円周率
	return Ans;
}