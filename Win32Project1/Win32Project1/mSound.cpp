#include "stdafx.h"
#include "mSound.h"


/*
*�T�E���h�̏�Ԃ��Ǘ�����N���X
*  _gl_mSoundObject �Ƃ������O�̃O���[�o���ϐ��Ƃ��Ď��̉����Ă����A
* �y�Ȃ̍Đ����s��
*  �� NORMAL�ELOOP�Đ�  �����ɍĐ�����Ȃ� 1 �ƂȂ�悤�ɊǗ�����
*  �� BACK�Đ��@���ʉ��Đ��p
*/
mSound::mSound()
{
	// ���ݍĐ����Ă���Ȃ͉����Ȃ�
	NowPlayingSoundHandle = 0;
}


mSound::~mSound()
{
}

// ��x�ǂݍ��񂾉����t�@�C�����ēx�ǂݍ��܂Ȃ����߂̊֐�
// ( mGraphic.MyLoadGraphic �Ɠ��l�̎d�g�� )
int mSound::MyLoadSoundMem(const TCHAR *FileName )
{
	int SoundHandle;

	int res = (int)SoundHandleObject.count(FileName);
	if (res == 0) {
		// �����[�h�̃T�E���h�ł����
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
	if (NOSOUND) return 0;

	// �Đ��������t�@�C��������A�����n���h�����擾
	int SoundHandle = MyLoadSoundMem(FileName);

	// �Đ����悤�Ƃ��Ă�����̂����ʉ��ȊO�̏ꍇ
	if (DX_PLAYTYPE_XXX != DX_PLAYTYPE_BACK) {
		// �����ɍĐ�������̂� 1 �B���������~�߂āA�V�����Ȃ𗬂��B
		if (NowPlayingSoundHandle == SoundHandle) {
			return 0; // �����Ȃ��Đ����悤�Ƃ�����I��
		} else if (NowPlayingSoundHandle != 0) {
			StopSoundMem(NowPlayingSoundHandle); // �O�ɍĐ����Ă����Ȃ��~
		}
		NowPlayingSoundHandle = SoundHandle; // �Đ����Ă���BGM��ۑ�
	}

	// �����t�@�C�������ۂɍĐ����鏈��
	return PlaySoundMem( SoundHandle , DX_PLAYTYPE_XXX );
}
