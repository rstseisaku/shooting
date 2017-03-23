#include "stdafx.h"

// グローバル変数の実体を定義
KeyControl* _gl_KeyControlObject = new KeyControl();
mGraphic* _gl_mGraphicObject = new mGraphic();


// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// ウィンドウモードに設定
	ChangeWindowMode(TRUE);
	// ウインドウのサイズを手動ではできず、且つウインドウのサイズに合わせて拡大もしないようにする		
	// SetWindowSizeChangeEnableFlag(FALSE, FALSE);
	// ウィンドウサイズの変更
	SetGraphMode(WindowSizeX, WindowSizeY, 32);
	SetWindowSize(WindowSizeX, WindowSizeY);

	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}

	mGameObject *GameMaster = new mGameObject();

	// 描画先を裏画面にする
	SetDrawScreen(DX_SCREEN_BACK);
	while (true) {
		//ウィンドウの×ボタンが押されたらループを抜ける
		if (ProcessMessage() != 0) break;
		ClearDrawScreen(); // 画面を消す

		GameMaster->MyUpdate();
		GameMaster->MyDraw();
		
		ScreenFlip(); //裏画面を表画面に反映
	}


	delete GameMaster; // メモリ開放

	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}