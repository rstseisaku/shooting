#pragma once

class KeyControl
{
public:
	// キーが押されているフレーム数を格納する
	KeyControl();
	~KeyControl();

	int Key[256];
	int Init();
	int Update();
};