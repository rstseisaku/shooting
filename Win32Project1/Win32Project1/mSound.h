#pragma once
class mSound
{
public:
	mSound();
	~mSound();
	int MyLoadSoundMem(const TCHAR*);
	int MyPlaySoundMem(const TCHAR * FileName, int DX_PLAYTYPE_XXX);

	// 既にある効果音であれば、ハンドルを返す
	std::map<const TCHAR*, int> SoundHandleObject;
	int NowPlayingSoundHandle;
};

