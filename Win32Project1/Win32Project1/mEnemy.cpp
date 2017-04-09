#include "stdafx.h"
#include "mEnemy.h"
#include "Enemy.h"


/*
* 敵オブジェクトを管理するためのクラス
* 難易度の上昇・管理している敵オブジェクトへの伝達なども行う
*/
mEnemy::mEnemy(BaseObject* _mEnemyBulletObject, BaseObject*  _PlayerObject) {
	// 初期化処理
	Layer = Layer_EnemyObject; // レイヤ設定
	mEnemyBulletObject = _mEnemyBulletObject; // 敵弾管理オブジェクトへのアドレスを格納
	PlayerObjectInstance = _PlayerObject; // プレイヤークラスへのアドレスを格納
	Level = 0; // レベルを0に設定
	Counter = 0; // レベル上昇カウンタを初期化

	// 敵オブジェクト生成
	AddObject(
		new Enemy(_T("Image/enemy1.png"),
		(mEnemyBullet *)mEnemyBulletObject,
		(PlayerObject *)PlayerObjectInstance,
		FieldCenterX,
		FieldCenterY));	
}

mEnemy::~mEnemy()
{
	// 子オブジェクトの消去
	MyDestructor();
}

void mEnemy::MyUpdate()
{
	// 子オブジェクトのUpdateを呼び出す
	for (auto itr = ObjectList.begin(); itr != ObjectList.end(); ++itr) {
		if ((*itr)->ObjectDeleteFlag) continue;
		((Enemy*)(*itr))->mEnemyObjectLevel = Level; // 敵オブジェクトとのレベル同期
		(*itr)->MyUpdate();
	}

	// レベル上昇
	Counter = ((++Counter) % 600);
	if ( Counter == 0) Level++;

	// プレイヤオブジェクトにレベルを伝達
	((PlayerObject*)PlayerObjectInstance)->EnemyLevel = Level;
}

void mEnemy::MyDraw()
{
	// 子オブジェクトの Draw 関数を呼び出す
	// ( 消去フラグが立っていたら消去する )
	for (auto itr = ObjectList.begin(); itr != ObjectList.end(); ) {
		if ((*itr)->ObjectDeleteFlag) {
			delete((*itr));
			itr = ObjectList.erase(itr); // 要素を削除、次要素を受け取る
			continue;
		}
		(*itr)->MyDraw();
		itr++;
	}
}

void mEnemy::MyPeculiarAction(BaseObject * PlayerObj) {
	// 特に何もしない
}
