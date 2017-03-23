#include "stdafx.h"

bool comp(BaseObject *& v1, BaseObject *& v2) {
	if (v1->Layer < v2->Layer) {
		return true;
	}
	else {
		return false;
	}
}

// ObjectList.sort(&comp);

mGameObject::mGameObject()
{
	_gl_KeyControlObject->Init();
	x = 0;
	y = 0;

	// オブジェクトを生成
	AddObject(new mEnemyBullet()); // 敵弾管理オブジェクト
	AddObject(new PlayerDecorationObject(_T("Image/PDObject.png"))); // プレイヤーデコレートオブジェクト
	AddObject(new PlayerObject(_T("Image/PlayerObject.png"), 0, 0)); // プレイヤーオブジェクト
	AddObject(new BackGround(_T("Image/BackGround1.png"), 288, 576)); // 背景オブジェクト
	AddObject(new Screen(_T("Image/Screen.png"), 512, 288)); // 背景オブジェクト

	ObjectList.sort( &comp );
}

mGameObject::~mGameObject()
{
}

void mGameObject::MyUpdate()
{
	// それぞれのオブジェクトのUpdate関数を呼び出す
	_gl_KeyControlObject->Update();
	for (auto itr = ObjectList.begin(); itr != ObjectList.end(); ++itr) {
		if ( (*itr)->ObjectDeleteFlag ) continue;
		(*itr)->MyUpdate();
	}
	DrawFormatString(5, 85, GetColor(0, 255, 255), _T("OK")); // 文字を描画する

	// 衝突判定を行う
	// カテゴリを探すだけなので、実処理以外はそこまで重くないはず
	// (イテレータの中身はポインタ)
	for (auto PlayerItr = ObjectList.begin(); PlayerItr != ObjectList.end(); ++PlayerItr) {
		if ( (*PlayerItr)->ObjectDeleteFlag ) continue;

		// プレイヤーオブジェクトを見つけたら(1つのみ)
		int ObjectLayer = (*PlayerItr)->Layer;
		if (ObjectLayer == Layer_PlayerObject) {

			// 弾オブジェクトとの衝突判定を行う
			for (auto itr = ObjectList.begin(); itr != ObjectList.end(); ++itr) {
				if ( (*itr)->ObjectDeleteFlag ) continue;

				int TargetobjectLayer = (*itr)->Layer;
				if (TargetobjectLayer == Layer_EnemyBullet || 
					TargetobjectLayer == Layer_PlayerDecorationObject) {
					// 敵弾管理オブジェクト。
					//  (敵弾管理オブジェクトの、固有処理は、保有バレットとの当たり判定)
					// デコレートオブジェクト
					//  (座標を合わせるだけ)
					(*itr)->MyPeculiarAction((*PlayerItr));
				}
			}
		}
	}
}

void mGameObject::MyDraw()
{
	for (auto itr = ObjectList.begin(); itr != ObjectList.end(); ++itr) {
		if ( (*itr)->ObjectDeleteFlag ) continue;
		(*itr)->MyDraw();
	}
	// DrawFormatString(x, y, GetColor(0, 255, 255), _T("Obj数[%d]"),  ObjectList.size() ); // 文字を描画する
}

void mGameObject::AddObject( BaseObject *obj )
{
	ObjectList.push_back(obj);
}

