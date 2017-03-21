#include "BaseObject.h"

#pragma once
class PlayerObject : public BaseObject
{
public:
	PlayerObject(const TCHAR * FileName);
	PlayerObject(const TCHAR * FileName, int _LeftX, int _UpperY);
	~PlayerObject();

	void InitCommon(const TCHAR * FileName); // constructor����

	// ��������
	void MyUpdate();
	void MyDraw();
	void MyPeculiarAction(BaseObject * obj);

	// �摜��12�ɕ����Ǎ�
	int GraphicHandle[100]; // �R���X�g���N�^�Œ�`
	int GraphicPattern;
	int AnimationInterval = 10;
	int AnimationCounter = 0;
	int RemainingPlayer;
};

