#pragma once

class KeyControl
{
public:
	// �L�[��������Ă���t���[�������i�[����
	KeyControl();
	~KeyControl();

	int Key[256];
	int Init();
	int Update();
};