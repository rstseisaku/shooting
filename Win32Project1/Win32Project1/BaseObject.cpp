#include "stdafx.h"
#include "BaseObject.h"


/*
* オブジェクトを設定するためのクラス
* AddObject() … 子オブジェクトの追加
* ObjectDelete() … 消去フラグを立てる。Update()・Draw()が呼ばれなくなる。
*　┗ 消去フラグが経っていたら、delete( *p ) を呼ぶ、という処理が別途必要。
*/
BaseObject::BaseObject()
{
}

BaseObject::BaseObject(const TCHAR *FileName) 
{
}


BaseObject::~BaseObject()
{
}

void BaseObject::AddObject(BaseObject * obj)
{
	// 子オブジェクトの追加
	ObjectList.push_back(obj);
}

void BaseObject::ObjectDelete()
{
	// 消去フラグを立てる。
	// Update() Draw()を呼ばなくするだけ
	ObjectDeleteFlag = true;
}

void BaseObject::MyDestructor()
{
	// 保持しているオブジェクトをすべて破棄
	// // 子オブジェクトも連鎖的に破棄する
	for (auto itr = ObjectList.begin(); itr != ObjectList.end(); ) {
		delete((*itr));
		itr = ObjectList.erase(itr); // 要素を削除、次要素を受け取る
	}
}

double BaseObject::GetCenterX()
{
	return CenterX;
}

double BaseObject::GetCenterY()
{
	return CenterY;
}

double BaseObject::GetDrawX()
{
	return CenterX - WidthX / 2;
}

double BaseObject::GetDrawY()
{
	return CenterY - HeightY / 2;
}