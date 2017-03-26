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

	void PrepareBom(BaseObject* EnemyBullet);
	void ActivateBom(BaseObject* EnemyBullet);
	int ColEllipsPoint(double PlayerX, double PlayerY, BaseObject2D* Elp);

	// 画像を12個に分割読込
	int GraphicHandle[100]; // コンストラクタで定義
	int GraphicPattern;
	int AnimationInterval = 10;
	int AnimationCounter = 0;
	int Life;
	int InvincibleTime;
	int Graze;
	double BomSize = 0.0;
	int GrazeHandle;
	int GrazeWidth;
	int GrazeHeight;

	BaseObject* EnemyBullet;
};

