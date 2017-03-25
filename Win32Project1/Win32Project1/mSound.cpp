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
	if (res == 0) { // �����[�h�̃T�E���h�ł����
		SoundHandle = LoadSoundMem(FileName);		if (SoundHandle == -1) {
			DrawFormatString(0, 70, GetColor(255, 0, 0), _T("�y�����t�@�C���ǂݍ��݂Ɏ��s���܂����z%s"), FileName); // ������`�悷��
			ScreenFlip();WaitKey();
		}
		SoundHandleObject[FileName] = SoundHandle;
	}
	else {
		SoundHandle = SoundHandleObject[FileName];
	}
	return SoundHandle;
}


// �v���C�^�C�v�́ANORMAL�EBACK�ELOOP��3��ށB
// �m�[�}���́A���1��ނ̍Đ��ƂȂ�悤�ɊǗ�����B
int mSound::MyPlaySoundMem( const TCHAR *FileName, int DX_PLAYTYPE_XXX )
{
	// DX_PLAYTYPE_NORMAL�@:�@�m�[�}���Đ�
	// DX_PLAYTYPE_BACK�@�@ : �o�b�N�O���E���h�Đ�
	// DX_PLAYTYPE_LOOP�@�@ : ���[�v�Đ�
	int SoundHandle = MyLoadSoundMem(FileName);
	if (DX_PLAYTYPE_XXX != DX_PLAYTYPE_BACK) { // �o�b�N�O���E���h�Đ��̏ꍇ�́A��~�����͕s�v�B
		if (NowPlayingSoundHandle == SoundHandle) {
			return 0; // �����Ȃ��Đ����悤�Ƃ�����I��
		} else if (NowPlayingSoundHandle != 0) {
			StopSoundMem(NowPlayingSoundHandle); // �O�ɍĐ����Ă����Ȃ��~
		}
		NowPlayingSoundHandle = SoundHandle; // �Đ����Ă���BGM��ۑ�
	}
	if ( NOSOUND ) return 0;
	return PlaySoundMem( SoundHandle , DX_PLAYTYPE_XXX );
}
