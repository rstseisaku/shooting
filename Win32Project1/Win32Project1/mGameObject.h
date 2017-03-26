#include "BaseObject.h"
#include "Screen.h"
#include "stdafx.h"

#pragma once
class mGameObject
{
public:
	mGameObject();
	~mGameObject();

	void MyUpdate();
	void MyDraw();
	void AddObject(BaseObject * obj);

	void MyUpdateGameplaying();

	void ClearObject();

	void SetObject();

	void ChangeStatus(int Status);

	void MyUpdateGamestart();

	void MyUpdateGameover();

	BaseObject* mEnemyBulletObject;
	PlayerObject* Player;
	Screen* mScreen;

	int GameStatus;

private:
	int x, y;
	int count = 0;
	std::list<BaseObject*> ObjectList;
};

