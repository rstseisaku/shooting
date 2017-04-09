#include "stdafx.h"
#include "mSound.h"


/*
*サウンドの状態を管理するクラス
*  _gl_mSoundObject という名前のグローバル変数として実体化しておき、
* 楽曲の再生を行う
*  ⇒ NORMAL・LOOP再生  同時に再生する曲は 1 つとなるように管理する
*  ⇒ BACK再生　効果音再生用
*/
mSound::mSound()
{
	// 現在再生している曲は何もない
	NowPlayingSoundHandle = 0;
}


mSound::~mSound()
{
}

// 一度読み込んだ音声ファイルを再度読み込まないための関数
// ( mGraphic.MyLoadGraphic と同様の仕組み )
int mSound::MyLoadSoundMem(const TCHAR *FileName )
{
	int SoundHandle;

	int res = (int)SoundHandleObject.count(FileName);
	if (res == 0) {
		// 未ロードのサウンドであれば
		SoundHandle = LoadSoundMem(FileName);		if (SoundHandle == -1) {
			DrawFormatString(0, 70, GetColor(255, 0, 0), _T("【音声ファイル読み込みに失敗しました】%s"), FileName); // 文字を描画する
			ScreenFlip();WaitKey();
		}
		SoundHandleObject[FileName] = SoundHandle;
	}
	else {
		SoundHandle = SoundHandleObject[FileName];
	}
	return SoundHandle;
}


// プレイタイプは、NORMAL・BACK・LOOPの3種類。
// ノーマルは、常に1種類の再生となるように管理する。
int mSound::MyPlaySoundMem( const TCHAR *FileName, int DX_PLAYTYPE_XXX )
{
	if (NOSOUND) return 0;

	// 再生したいファイル名から、音声ハンドルを取得
	int SoundHandle = MyLoadSoundMem(FileName);

	// 再生しようとしているものが効果音以外の場合
	if (DX_PLAYTYPE_XXX != DX_PLAYTYPE_BACK) {
		// 同時に再生するものは 1 つ。旧音声を止めて、新しく曲を流す。
		if (NowPlayingSoundHandle == SoundHandle) {
			return 0; // 同じ曲を再生しようとしたら終了
		} else if (NowPlayingSoundHandle != 0) {
			StopSoundMem(NowPlayingSoundHandle); // 前に再生していた曲を停止
		}
		NowPlayingSoundHandle = SoundHandle; // 再生しているBGMを保存
	}

	// 音声ファイルを実際に再生する処理
	return PlaySoundMem( SoundHandle , DX_PLAYTYPE_XXX );
}
