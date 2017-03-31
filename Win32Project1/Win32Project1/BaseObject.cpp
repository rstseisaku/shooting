#include "stdafx.h"
#include "BaseObject.h"


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
	ObjectList.push_back(obj);
}

void BaseObject::ObjectDelete()
{
	ObjectDeleteFlag = true;
}

void BaseObject::MyDestructor()
{
	// �ێ����Ă���I�u�W�F�N�g�����ׂĔj��
	for (auto itr = ObjectList.begin(); itr != ObjectList.end(); ) {
		delete((*itr));
		itr = ObjectList.erase(itr); // �v�f���폜�A���v�f���󂯎��
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