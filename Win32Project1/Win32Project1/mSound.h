#pragma once
class mSound
{
public:
	mSound();
	~mSound();
	int MyLoadSoundMem(const TCHAR*);
	int MyPlaySoundMem(const TCHAR * FileName, int DX_PLAYTYPE_XXX);

	// Šù‚É‚ ‚éŒø‰Ê‰¹‚Å‚ ‚ê‚ÎAƒnƒ“ƒhƒ‹‚ğ•Ô‚·
	std::map<const TCHAR*, int> SoundHandleObject;
	int NowPlayingSoundHandle;
};

