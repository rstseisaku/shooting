#pragma once
class mSound
{
public:
	mSound();
	~mSound();
	int MyLoadSoundMem(const TCHAR*);
	int MyPlaySoundMem(const TCHAR * FileName, int DX_PLAYTYPE_XXX);

	// ���ɂ�����ʉ��ł���΁A�n���h����Ԃ�
	std::map<const TCHAR*, int> SoundHandleObject;
	int NowPlayingSoundHandle;
};

