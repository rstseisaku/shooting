#pragma once
#include "BaseObject2D.h"
class Screen :
	public BaseObject2D
{
public:
	Screen();
	Screen(const TCHAR * FileName, int _CenterX, int _CenterY, PlayerObject* Player);
	~Screen();
	void MyUpdate();
	void MyDraw();
	void MyPeculiarAction(BaseObject * obj);
	void ShowLife();
	void ShowScore();


	PlayerObject* PlayerObj;
	int ScoreFont;
	int ScoreLength;
	double TimeScore;
	double GrazeScore;
	int HighScore;
	int LifeGraphic;
};

