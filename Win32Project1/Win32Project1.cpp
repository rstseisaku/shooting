#include "stdafx.h"

// �O���[�o���ϐ��̎��̂��`
KeyControl* _gl_KeyControlObject = new KeyControl();
mGraphic* _gl_mGraphicObject = new mGraphic();


// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// �E�B���h�E���[�h�ɐݒ�
	ChangeWindowMode(TRUE);
	// �E�C���h�E�̃T�C�Y���蓮�ł͂ł����A���E�C���h�E�̃T�C�Y�ɍ��킹�Ċg������Ȃ��悤�ɂ���		
	// SetWindowSizeChangeEnableFlag(FALSE, FALSE);
	// �E�B���h�E�T�C�Y�̕ύX
	SetGraphMode(WindowSizeX, WindowSizeY, 32);
	SetWindowSize(WindowSizeX, WindowSizeY);

	if (DxLib_Init() == -1)		// �c�w���C�u��������������
	{
		return -1;			// �G���[���N�����璼���ɏI��
	}

	mGameObject *GameMaster = new mGameObject();

	// �`���𗠉�ʂɂ���
	SetDrawScreen(DX_SCREEN_BACK);
	while (true) {
		//�E�B���h�E�́~�{�^���������ꂽ�烋�[�v�𔲂���
		if (ProcessMessage() != 0) break;
		ClearDrawScreen(); // ��ʂ�����

		GameMaster->MyUpdate();
		GameMaster->MyDraw();
		
		ScreenFlip(); //����ʂ�\��ʂɔ��f
	}


	delete GameMaster; // �������J��

	DxLib_End();				// �c�w���C�u�����g�p�̏I������

	return 0;				// �\�t�g�̏I�� 
}