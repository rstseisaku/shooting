#include "BaseObject.h"


#pragma once
class PlayerObject : public BaseObject
{
public:
	PlayerObject(const TCHAR * FileName);
	PlayerObject(const TCHAR * FileName, int _LeftX, int _UpperY, BaseObject* mEnemyBulletObject);
	~PlayerObject();

	void InitCommon(const TCHAR * FileName); // constructor共通

											 // 実装する
	void MyUpdate();
	void MyDraw();
	void MyPeculiarAction(BaseObject * obj);

	void ActivateBom();
	void CloseBom();
	int ColEllipsPoint(double PlayerX, double PlayerY, BaseObject2D* Elp);

	// 画像を12個に分割読込
	int GraphicHandle[100]; // コンストラクタで定義
	int GraphicPattern;
	int AnimationInterval = 10;
	int AnimationCounter = 0;
	int Life;
	int InvincibleTime;
	int GrazeScore;
	double EraseScore;
	double BomSize;
	int GrazeHandle;
	int EnemyLevel;
	bool UsingBom = FALSE;
	int Counter;
	int BomX;
	int BomY;
	double tmp;
	bool ShowScore;
	int ScoreFont;

	int GetItemNum; // 拾ったアイテムの個数
	int GetRareItemNum;  // 拾ったハイスコアアイテムの個数

	BaseObject* EnemyBullet;
};

