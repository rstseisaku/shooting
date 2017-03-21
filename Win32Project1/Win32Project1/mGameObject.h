#include "BaseObject.h"
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

private:
	int x, y;
	int count = 0;
	std::list<BaseObject*> ObjectList;
};

