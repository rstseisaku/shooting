#include "stdafx.h"


/*
* キー入力の状態を管理するクラス
* _gl_KeyControlObject という名前のグローバル変数として実体化しておき、
* 毎フレーム Update 関数を呼び出し更新する
* ( グローバル変数なので、どこからでも呼び出せる )
*/
KeyControl::KeyControl()
{
}

KeyControl::~KeyControl()
{
}

int KeyControl::Init() {
	memset(Key, 0, 256);
	return 0;
}

int KeyControl::Update() {
	char tmpKey[256]; // 現在のキーの入力状態を格納する
	GetHitKeyStateAll(tmpKey); // 全てのキーの入力状態を得る
	for (int i = 0; i<256; i++) {
		if (tmpKey[i] != 0) { // i番のキーコードに対応するキーが押されていたら
			if (Key[i] < 2)
			Key[i]++;     // 加算
			//1 押された時　2 押されている

		}
		else {              // 押されていなければ
			if (Key[i] > 0)
				Key[i] = -1;	//離された時
			else
				Key[i] = 0;   // 0にする
			//離されている
		}
	}
	return 0;
}
