#include "stdafx.h"


/*
* �L�[���͂̏�Ԃ��Ǘ�����N���X
* _gl_KeyControlObject �Ƃ������O�̃O���[�o���ϐ��Ƃ��Ď��̉����Ă����A
* ���t���[�� Update �֐����Ăяo���X�V����
* ( �O���[�o���ϐ��Ȃ̂ŁA�ǂ�����ł��Ăяo���� )
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
	char tmpKey[256]; // ���݂̃L�[�̓��͏�Ԃ��i�[����
	GetHitKeyStateAll(tmpKey); // �S�ẴL�[�̓��͏�Ԃ𓾂�
	for (int i = 0; i<256; i++) {
		if (tmpKey[i] != 0) { // i�Ԃ̃L�[�R�[�h�ɑΉ�����L�[��������Ă�����
			if (Key[i] < 2)
			Key[i]++;     // ���Z
			//1 �����ꂽ���@2 ������Ă���

		}
		else {              // ������Ă��Ȃ����
			if (Key[i] > 0)
				Key[i] = -1;	//�����ꂽ��
			else
				Key[i] = 0;   // 0�ɂ���
			//������Ă���
		}
	}
	return 0;
}
