#include "stdafx.h"
#include "mSound.h"


mSound::mSound()
{
	NowPlayingSoundHandle = 0;
}


mSound::~mSound()
{
}

int mSound::MyLoadSoundMem(const TCHAR *FileName )
{
	int SoundHandle;
	int res = (int)SoundHandleObject.count(FileName);
	if (res == 0) { // 未ロードのサウンドであれば
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
	// DX_PLAYTYPE_NORMAL　:　ノーマル再生
	// DX_PLAYTYPE_BACK　　 : バックグラウンド再生
	// DX_PLAYTYPE_LOOP　　 : ループ再生
	int SoundHandle = MyLoadSoundMem(FileName);
	if (DX_PLAYTYPE_XXX != DX_PLAYTYPE_BACK) { // バックグラウンド再生の場合は、停止処理は不要。
		if (NowPlayingSoundHandle == SoundHandle) {
			return 0; // 同じ曲を再生しようとしたら終了
		} else if (NowPlayingSoundHandle != 0) {
			StopSoundMem(NowPlayingSoundHandle); // 前に再生していた曲を停止
		}
		NowPlayingSoundHandle = SoundHandle; // 再生しているBGMを保存
	}
	if ( NOSOUND ) return 0;
	return PlaySoundMem( SoundHandle , DX_PLAYTYPE_XXX );
}
