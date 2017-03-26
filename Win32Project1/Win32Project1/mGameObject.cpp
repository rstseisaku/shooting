#include "stdafx.h"

bool comp(BaseObject *& v1, BaseObject *& v2) {
	if (v1->Layer < v2->Layer) {
		return true;
	}
	else {
		return false;
	}
}

// コンストラクタ
mGameObject::mGameObject()
{
	GameStatus = GAMESTART;
}

mGameObject::~mGameObject()
{
	//いじった
}

void mGameObject::MyUpdate()
{
	_gl_KeyControlObject->Update(); // キーボード状態更新
	if (GameStatus == GAMEPLAYING) {
		MyUpdateGameplaying();
	} else if ( GameStatus == GAMEOVER ) {
		MyUpdateGameover();
	} 
	else if (GameStatus == GAMESTART) {
		MyUpdateGamestart();
	}
}

void mGameObject::MyDraw()
{
	for (auto itr = ObjectList.begin(); itr != ObjectList.end(); ++itr) {
		if ((*itr)->ObjectDeleteFlag) continue;
		(*itr)->MyDraw();
	}
	// DrawFormatString(x, y, GetColor(0, 255, 255), _T("Obj数[%d]"),  ObjectList.size() ); // 文字を描画する
}

void mGameObject::AddObject(BaseObject *obj)
{
	ObjectList.push_back(obj);
}

void mGameObject::ClearObject()
{
	// 登録してあるオブジェクトを消去
	// (ObjectList.Clearは子オブジェクトが消えないので使わない)
	for (auto itr = ObjectList.begin(); itr != ObjectList.end(); ) {
		int ObjectLayer = (*itr)->Layer;
		delete((*itr)); // デストラクタの中で、必要に応じて子オブジェクト解放処理を書く
		itr = ObjectList.erase(itr); // 要素を削除、次要素を受け取る
	}
}

// GameStatusに応じてオブジェクトを設置
void mGameObject::SetObject()
{
	if (GameStatus == GAMESTART) {
		// GAMESTART開始時に必要なものをセット
		// (特になし)
	} else if (GameStatus == GAMEPLAYING) {
		// ゲームプレイ開始時に必要なものをセット
		mEnemyBulletObject = new mEnemyBullet();
		Player = new PlayerObject(_T("Image/PlayerObject.png"), 0, 0); // プレイヤーオブジェクト
		AddObject(mEnemyBulletObject); // 敵弾管理オブジェクト
		AddObject(new mEnemy(mEnemyBulletObject,Player)); // 敵管理オブジェクト。敵弾管理オブジェクトを一緒に渡す。
		AddObject(new PlayerDecorationObject(_T("Image/PDObject.png"))); // プレイヤーの当たり判定を表示
		AddObject(Player);
		AddObject(new BackGround(_T("Image/BackGround1.png"), 288, 576)); // 背景オブジェクト
		mScreen = new Screen(_T("Image/Screen.png"), 512, 288, Player);
		AddObject( mScreen );
		ObjectList.sort(&comp);
	} else if (GameStatus == GAMEOVER) {
		// ゲームオーバー開始時に必要なものをセット
		// 全滅時の背景を表示
		AddObject(new BackGround(_T("Image/gameover.png"), WindowCenterX, WindowCenterY));
	}

}

// ゲーム状態の状態遷移。
// オブジェクトの再配置を行う。
void mGameObject::ChangeStatus( int Status )
{
	GameStatus = Status ; // GameStatusをGAMEOVERに切り替える
	ClearObject();
	SetObject();
}


/*
 * =====================================================
 * Statusに応じたUpdate処理
 * =====================================================
 */

 // GameStatusがGamestartなら呼び出す処理。
 // ゲームの初期化処理を担当する。
void mGameObject::MyUpdateGamestart()
{
	// 初期化処理。終了後、そのままプレイ中状態に遷移
	_gl_KeyControlObject->Init();
	_gl_mSoundObject->MyPlaySoundMem( _T("Sound/BGM1.mp3"), DX_PLAYTYPE_LOOP );
	_gl_mSoundObject->MyPlaySoundMem(_T("Sound/BGM1.mp3"), DX_PLAYTYPE_LOOP);
	_gl_mSoundObject->MyPlaySoundMem( _T("Sound/BGM2.mp3"), DX_PLAYTYPE_LOOP );
	_gl_mSoundObject->MyPlaySoundMem( _T("Sound/BGM1.mp3"), DX_PLAYTYPE_LOOP );
	x = 0;
	y = 0;

	// プレイ中状態にチェンジ。
	ChangeStatus(GAMEPLAYING);
}

// GameStatusがGameOverなら呼び出す処理。
// ゲームの終了処理を担当する。
void mGameObject::MyUpdateGameover()
{
	// ゲームオーバー画面での処理
	if (_gl_KeyControlObject->Key[KEY_INPUT_ESCAPE] == 1)
		ChangeStatus( GAMESTART );
}

// GameStatusがGamePlayingなら呼び出す処理。
// ゲームのメイン処理を担当する。
void mGameObject::MyUpdateGameplaying()
{
	// それぞれのオブジェクトのUpdate関数を呼び出す
	for (auto itr = ObjectList.begin(); itr != ObjectList.end(); ++itr) {
		if ((*itr)->ObjectDeleteFlag) continue;
		(*itr)->MyUpdate();
	}

	// ゲームオーバー判定
	if (Player->Life == -1) {
		_gl_mSoundObject->MyPlaySoundMem(_T("Sound/BGM2.mp3"), DX_PLAYTYPE_LOOP);
		ChangeStatus( GAMEOVER );
	}

	// 衝突判定を行う
	// カテゴリを探すだけなので、実処理以外はそこまで重くない
	// (イテレータの中身はポインタである)
	for (auto PlayerItr = ObjectList.begin(); PlayerItr != ObjectList.end(); ++PlayerItr) {
		if ((*PlayerItr)->ObjectDeleteFlag) continue;
		// プレイヤーオブジェクトを見つけたら(1つのみ)
		int ObjectLayer = (*PlayerItr)->Layer;
		if (ObjectLayer == Layer_PlayerObject) {
			// 弾オブジェクトとの衝突判定を行う
			for (auto itr = ObjectList.begin(); itr != ObjectList.end(); ++itr) {
				if ((*itr)->ObjectDeleteFlag) continue;

				int TargetobjectLayer = (*itr)->Layer;
				if (TargetobjectLayer == Layer_EnemyBullet ||
					TargetobjectLayer == Layer_PlayerDecorationObject) {
					// ・敵弾管理オブジェクト。
					//  　―敵弾管理オブジェクトの、固有処理は、保有バレットとの当たり判定)
					// ・デコレートオブジェクト
					//  　―座標を合わせるだけ)
					(*itr)->MyPeculiarAction((*PlayerItr));
				}
			}
		}
	}
}

